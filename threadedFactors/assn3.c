// Program 3 pthreads
// Michael Shipley CS 3060 Fall 2021
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h> // for malloc and free
void *findFactors(void *param);

struct container {
	int input; //Number to be factored
	int output[sizeof(int)]; // It actually would be better as log base 2 of input. but hey. I work with what I got. 
};

int main (int argc, char* argv[]) {
	pthread_t tid[argc-1]; //Thread IDs in an array
	//pthread_attr_t attr; //Used for Thread attributes.
	struct container *threadMemory [(argc-1)]; //Be warned this is a larger number of space than we will ever use.

	// Ignore this, my brother says a struct will be easier with the void ptr.
	// int[(argc-1)][sizeof(int)] thread_Array; 
	//The 1st level array will reflect an id for each element in argv, the second will hold values for factors
	
	if(argc == 1) {
		printf("\nusage: ./p3 <number to factor> ...\n");
		// free(threadMemory); //always pair your frees and mallocs.
		return 0; //This is an acceptable use.
	}
	for(int i = 2; i <= argc; i++) {
		//pthread_attr(&attr); //Default Attributes
		printf("%d",i);
		threadMemory[i-2]->input = atoi(argv[i]); //The input in the array for our struct is assigned our argument.
		pthread_create(&tid[i],NULL,&findFactors,&threadMemory[i-2]); 
		//create the thread in the array of threads, with default attributes, 
		//give it the function handle for our equation, and the struct as a perameter for that function. 
	} 
	// I am hoping this breakup will keep anything from joining before anything is created.
	for(int i = 2; i <= argc; i++){
		pthread_join(tid[i], NULL); // Should wait till they are done asyncronously.
		printf("\n%s: ",argv[i]);
		for( int j =0; j <=argc; j++){
			if (threadMemory[i-2]->output[j] == 0) break;
			printf("%d ",threadMemory[i-2]->output[j]); //Prints each factor.
		}
		printf("\n"); // Just an endl.
	}
	// free(threadMemory);
	return 0;
}

void *findFactors(void *param){
	struct container *c = (struct container*)param; //c style cast to the struct type.
	int i = 3; // This is our factor.
	int j = 0; // This is to keep track of where we are in our output.
	while( c->input%2 ==0)
	{
		c->output[j] = 2;
		j++;
		c->input = c->input/2;
	}
	while (i*i <= c->input) {
		if(c->input%i==0){
			c->output[j] = i;
			j++;
			c->input = c->input/i;
		}
		else{
			i= i+2;
		}	
	}
	if (c->input!=0) c->output[j] = c->input;
	c->output[j+1] = 0; //This gives me a terminating number on the other side.
	pthread_exit(0);
}
