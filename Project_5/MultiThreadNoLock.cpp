#ifndef Project5
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define BUFFER_SIZE (20)
#define MAX_INT 65536

int *buffer;
int counter;
int in;
int out;

void *producer(void *ptr) {
	int value = 1;
	while (1) {
		while (counter == BUFFER_SIZE)
			; /* do nothing */

		buffer[in] = value++;
		in = (in + 1) % BUFFER_SIZE;
		counter++;
	}
	pthread_exit(0);
}

void *consumer(void *ptr) {
	int last = 0;
	while (last < MAX_INT) {
		while (counter == 0)
			; /* do nothing */

		last++;

		if (last != buffer[out]) {
			printf("Error at value %d! I was expecting %d\n", buffer[out], last);
			exit(-1);
		}

		out = (out + 1) % BUFFER_SIZE;
		counter--;
	}
	pthread_exit(0);
}

int main(int argc,char* argv[]) {
	pthread_t produce;
	pthread_t consume;
	buffer = *(int**)malloc(sizeof(int) * BUFFER_SIZE);
	counter = 0;
	in = 0;
	out = 0;

	pthread_create(&produce, NULL, producer, NULL);

	pthread_create(&consume, NULL, consumer, NULL);

	pthread_join(produce, NULL);
	pthread_join(consume, NULL);

	return 0;
}
#endif