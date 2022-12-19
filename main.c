/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee <yejlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 12:47:31 by yejlee            #+#    #+#             */
/*   Updated: 2022/12/19 19:36:34 by yejlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void check_finish(t_args *arg)
{
	int	i;
	
	while (!arg->done)
	{
		i = -1;
		while (++i < arg->num_philo && !arg->die)
		{
			pthread_mutex_lock(&arg->monitor);
			if (get_time() - arg->philo[i].last_eat > arg->time_to_die)
			{
				print_message(&arg->philo[i], get_time() - arg->time_to_start, DIE);
				arg->die = 1;
			}
			pthread_mutex_unlock(&arg->monitor);
		}
		if (arg->die)
			break ;
		i = 0;
		while(arg->num_must_eat != -1 && i < arg->num_philo 
			&& arg->philo[i].eat_cnt >= arg->num_must_eat)
			i++;
		if (arg->num_philo == i)
			arg->done = 1;
	}
}

static void	*start_routine(void *thread) //스타트 루틴으로 변경 예정
{
	t_philo	*philo;
	t_args 	*arg;

	philo = (t_philo *)thread;
	if (philo->num % 2 != 0)
		usleep(philo->arg->time_to_eat * 1000);
	while (!philo->arg->die) //enum의 DIED 로 변경
	{
		take_fork(philo);
		eat(philo);
		if (philo->arg->done)
			break ;
		sleep_and_think(philo);
	}
}

static void take_fork(t_philo *philo)
{
	if (philo[i].num % 2 == 0)
		pthread_mutex_lock(&philo->arg->fork[philo->left_f]);
	else
		pthread_mutex_lock(&philo->arg->fork[philo->right_f]);
	print_message(philo, get_time() - philo->arg->time_to_start, TAKE_FORK);
	if (philo[i].num % 2 == 0)
		pthread_mutex_lock(&philo->arg->fork[philo->right_f]);
	else
		pthread_mutex_lock(&philo->arg->fork[philo->left_f]);
	print_message(philo, get_time() - philo->arg->time_to_start, TAKE_FORK);
}

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->monitor);
	philo->last_eat = get_time();
	print_message(philo, philo->last_eat - philo->arg->time_to_start, EATING);
	pthread_mutex_unlock(&philo->arg->monitor);
	while (get_time() < philo->last_eat + philo->info->time_to_eat)
		;
	philo->eat_cnt++;
	pthread_mutex_unlock(&philo->arg->fork[philo->left_f]);
	pthread_mutex_unlock(&philo->arg->fork[philo->right_f]);
}

static void sleep_and_think(t_philo *philo)
{
	t_args *arg;
	long	think_time;
	long	sleep_time;

	philo->last_sleep = get_time();
	sleep_time = philo->last_sleep - philo->arg->time_to_start;
	print_message(philo, sleep_time, SLEEPING);
	while (get_time() < philo->last_sleep + philo->arg->time_to_sleep)
		continue; //여기서 continue는 의미 없음.
	think_time = get_time() - philo->arg->time_to_start;
	print_message(philo, think_time, THINKING);
	usleep(200);
}

static void init_mutex(t_args *arg)
{
	int i;

	arg->fork = malloc(sizeof(pthread_mutex_t) * arg->num_philo);
	if (arg->fork == NULL)
	{
		ft_putendl_fd("Error malloc for fork", 1);
		return (NULL);
	}
	i = -1;
	if (++i < arg->num_philo)
	{
		pthread_mutex_init(&arg->fork[i], NULL);
	}
	pthread_mutex_init(&arg->monitor, NULL);
	pthread_mutex_init(&arg->messanger, NULL);
}

static void stock_and_create(t_args *arg)
{
	int	i;
	t_philo *philo;

	i = -1;
	arg = malloc(sizeof(t_args));
	arg->philo = malloc(sizeof(t_philo) * arg->num_philo);
	while (++i < arg->num_philo)
	{
		arg->philo[i].num = i; //0부터 시작하는 방법
		if (phread_create(&arg->philo[i].tid, NULL, start_routine, &arg->philo[i]) < 0)
			print_err("Error in Pthread_create for philosophers, check this");
	}
}

/*static void free_and_join(t_args *arg)
{
	int i;

	i = -1;
	while (++i < arg->num_philo)
		pthread_join(arg->philo[i].tid, NULL);
	free(arg->philo);
	free(arg);
	pthread_mutex_destroy(&arg->messanger);
	pthread_mutex_destroy(&arg->monitor);
}*/
		
int	main(int ac, char *av[])
{
	int		i;
	t_args	*arg;
	t_philo	*philo;

	memset(&arg, 0, sizeof(arg));
	if (ac != 5 || ac != 6)
		return (print_err("Error in arguments ac for philosophers."));
	if (init_all_philo(ac, av, &arg))
		return (1);
	if (start_philo)
		return (1);
	return (0);
}