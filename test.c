#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <philo.h>


size_t	get_time(size_t time_start)
{
	struct timeval current;

	gettimeofday(&current, 0);
	return (current.tv_sec * 1000 * 1000 + current.tv_usec- time_start);
}

void	signal_error(void)
{
	printf("Error, verify number of arguments!"\n);
	exit (1);
}

void	*abc(void *arg)
{
	char *name;
	int i;
	int cnt;
	pthread_mutex_t mutex_c;

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
	return ((void *)arg);
}

int main(void)
{
	pthread_t ph1, ph2, ph3, ph4;
	pthread_mutex_t mutex_c;

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

int	main(int ac, char *av[])
{
	if (av[5] || av[6] != 0)
		signal_error();
	num_philo = av[1];
	time_to_die = av[2];
	time_to_eat = av[3];
	time_to_sleep = av[4];
	num_must_eat = av[5];


}
