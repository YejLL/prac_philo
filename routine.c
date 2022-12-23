/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee <yejlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 15:03:44 by yejlee            #+#    #+#             */
/*   Updated: 2022/12/23 11:18:38 by yejlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_fork(t_philo *philo)
{
	if (philo->arg->num_philo == 1)
	{
		print_message(philo, get_time() - philo->arg->start_at, TAKE_FORK);
		return (1);
	}
	if (philo->num % 2 == 0)
		pthread_mutex_lock(&philo->arg->fork[philo->right_f]);
	else
		pthread_mutex_lock(&philo->arg->fork[philo->left_f]);
	print_message(philo,
		get_time() - philo->arg->start_at, TAKE_FORK);
	if (philo->num % 2 == 0)
		pthread_mutex_lock(&philo->arg->fork[philo->left_f]);
	else
		pthread_mutex_lock(&philo->arg->fork[philo->right_f]);
	print_message(philo,
		get_time() - philo->arg->start_at, TAKE_FORK);
	return (0);
}

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->monitor);
	philo->last_eat = get_time();
	print_message(philo, philo->last_eat - philo->arg->start_at, EATING);
	pthread_mutex_unlock(&philo->arg->monitor);
	while (get_time() < philo->last_eat + philo->arg->time_to_eat)
		;
	philo->eat_cnt++;
	pthread_mutex_unlock(&philo->arg->fork[philo->right_f]);
	pthread_mutex_unlock(&philo->arg->fork[philo->left_f]);
}

static void	sleep_and_think(t_philo *philo)
{
	philo->last_sleep = get_time();
	print_message(philo, philo->last_sleep - philo->arg->start_at, SLEEPING);
	while (get_time() < philo->last_sleep + philo->arg->time_to_sleep)
		;
	print_message(philo, get_time() - philo->arg->start_at, THINKING);
}

void	*start_ph(void *thread)
{
	t_philo	*philo;

	philo = (t_philo *)thread;
	if (philo->num % 2 == 0)
		usleep(philo->arg->time_to_eat * 1000);
	while (!philo->arg->die)
	{
		if (take_fork(philo) == 1)
			break ;
		eat(philo);
		if (philo->arg->done)
			break ;
		sleep_and_think(philo);
		usleep(1000);
	}
	return (NULL);
}
