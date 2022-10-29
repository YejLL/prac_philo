#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct	s_args
{
	int num_philo;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int num_must_eat;
}		t_args;



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

/*int main(void)
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
}*/

int	main(int ac, char *av[])
{
	t_args *arg;

	if (ac != 5 || ac != 6)
		signal_error();
	memeset(&arg, '\0', sizeof(t_args));
	arg->num_philo = ft_atoi(av[1]);
	arg->time_to_die = ft_atoi(av[2]);
	arg->time_to_eat = ft_atoi(av[3]);
	arg->time_to_sleep = ft_atoi(av[4]);
	arg->num_must_eat = ft_atoi(av[5]);



}
