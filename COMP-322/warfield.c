#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int max = 6;
int global_bad = 0;

void* zero(void* args)
{
	int g = 0;
	do
	{
		if (global_bad % 2 == 0)
		{
			printf("0");
			++global_bad;
			g = (global_bad + 1) / 2;
		}
	}
	while (g < max);
}

void* even(void* args)
{
	int g = 0;
	do
	{
		if (global_bad % 2 != 0)
		{
			g = (global_bad + 1) / 2;
			if (g % 2 == 0)
			{
				printf("%d", g);
				++global_bad;
			}
		}
	}
	while (g < max);
}
void* odds(void* args)
{
	int g = 0;
	do
	{
		if (global_bad % 2 != 0)
		{
			g = (global_bad + 1) / 2;
			if (g % 2 != 0)
			{
				printf("%d", g);
				++global_bad;
			}
		}
	}
	while (g < max);
}

int main(int argc, char **argv)
{
	if (argc > 1) { max = atoi(argv[1]); }

	pthread_t tid[3];
	pthread_create(&tid[0], NULL, zero, NULL);
	pthread_create(&tid[1], NULL, odds, NULL);
	pthread_create(&tid[2], NULL, even, NULL);

	for (int i = 0; i < 3; i++)
	{
		pthread_join(tid[i], NULL);
	}
	printf("\n");

	pthread_exit(NULL);
	return 0;
}
