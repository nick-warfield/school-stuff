#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

// barrier.h
void *worker(void *);
int barrier_init(int, pthread_barrier_t *);

#define MAX_THREAD_COUNT 5
int main(int argc, char **argv)
{
	srand(time(NULL));
	if (argc != 2)
	{
		fprintf(stderr, "Ussage: ./testbarrier <number of threads>\n");
		return -1;
	}

	int number = atoi(argv[1]);
	if (number > MAX_THREAD_COUNT) { return -1; }

	pthread_barrier_t barrier;
	if (barrier_init(number, &barrier) != 0) { return -1; }

	pthread_t workers[number];
	for (int i = 0; i < number; ++i)
	{
		pthread_create(&workers[i], NULL, worker, &barrier);
	}

	for (int i = 0; i < number; ++i)
	{
		pthread_join(workers[i], 0);
	}

	return 0;
}

int barrier_init(int threads, pthread_barrier_t *barrier)
{
	return pthread_barrier_init(barrier,  NULL, threads);
}

#define MAX_SLEEP_TIME 7
void *worker(void *barrier)
{
	int sleep_time = rand() % MAX_SLEEP_TIME;
	printf("Sleeping for %d seconds\n", sleep_time);
	sleep(sleep_time);

	pthread_barrier_wait((pthread_barrier_t *)barrier);
	printf("Out of the Barrier\n");
}
