#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>
#include "philo.h"

static long long	get_time(size_t time_start)
{
	struct timeval current;

	gettimeofday(&current, 0);
	return (current.tv_sec * 1000 * 1000 + current.tv_usec- time_start);
}

static void	signal_error(void)
{
	printf("Error, verify number of arguments!\n");
	exit (1);
}

void	*act(void *thread)
{
	int cnt = 0;
	t_philo *philo;
	//pthread_mutex_t pause;

	philo = thread;
	//pthread_mutex_lock(&pause);
	printf("%d is eating and tid: [%ld\n]", philo->num, philo->tid);
	printf("Done\n");
	//pthread_mutex_unlock(&pause);
}

int	main(int ac, char *av[])
{
	int	i;
	int	tmp;
	t_args *arg;
	t_philo *philo;

	i = 0;
	/*if (ac != 5 || ac != 6)
		signal_error();*/
	//memset(&arg, '\0', sizeof(t_args));
	//printf("[%d] print time here\n", get_time);
	arg = malloc(sizeof(t_args));
	arg->num_philo = ft_atoi(av[1]);
	arg->philo = malloc(sizeof(t_philo) * arg->num_philo);
	printf("num_philo : %d\n", arg->num_philo);
	/*arg->time_to_die = ft_atoi(av[2]);
	arg->time_to_eat = ft_atoi(av[3]);
	arg->time_to_sleep = ft_atoi(av[4]);
	arg->num_must_eat = ft_atoi(av[5]);*/
	/*philo = (t_philo *)malloc(sizeof(t_philo) * arg->num_philo);
	if (!philo)
		signal_error();*/
	i = -1;
	while (++i < arg->num_philo)
	{
		arg->philo[i].num = i;
	}
	i = -1;
	while (++i < arg->num_philo)
	{
		pthread_create(&arg->philo[i].tid, NULL, act, &arg->philo[i]);
		//pthread_join(philo[i].tid, NULL);
	}
	i = -1;
	while (++i < arg->num_philo)
		pthread_join(arg->philo[i].tid, NULL);
	free(arg->philo);
	free(arg);
	return (0);
}