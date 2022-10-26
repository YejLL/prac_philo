#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int cnt;
pthread_mutex_t mutex_c;

void	*abc(void *arg)
{
	char *name;
	int i;

	name = (char *)arg;
	pthread_mutex_lock(&mutex_c);
	cnt = 0;
	while (i < 14)
	{
		printf("%s count: %d\n", name, cnt);
		cnt++;
		usleep(100);
		i++;
	}
	pthread_mutex_unlock(&mutex_c);
	printf("test here %s\n", name);
	//return ((void *)arg);
}

int main(void)
{
	pthread_t ph1, ph2, ph3, ph4;

	pthread_create(&ph1, NULL, abc, (void *)"thread1");
	pthread_create(&ph2, NULL, abc, (void *)"thread2");
	pthread_create(&ph3, NULL, abc, (void *)"thread3");
	pthread_create(&ph4, NULL, abc, (void *)"thread4");
	pthread_join(ph1, NULL);
	pthread_join(ph2, NULL);
	pthread_join(ph3, NULL);
	pthread_join(ph4, NULL);
	pthread_mutex_destroy(&mutex_c);
	exit(0);
}
