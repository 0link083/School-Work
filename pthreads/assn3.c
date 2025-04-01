// assn3.c
// run using "./assn3" 

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

void *thread_func(void *p) {
	int *pnum = (int *)p;
}

int main(int argc, char* argv[]) {
	if (argc == 1) { // Assume this means input via console;
		
	}
	else if (argc == 2) {
		// Take 2nd argument as input file
	}
	num[n];

	pthread_t thread_handle;

	pthread_create(&thread_handle, NULL, thread_func, num);

	pthread_join(thread_handle, NULL)

	return 0;
}

void display(int a, int b, int c, int d) {
	printf("The product of %d, %d, and %d is %d", a, b, c, d);
}
int add(int a, int b, int c) {
	return a*b*c;
}