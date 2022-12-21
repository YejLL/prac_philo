/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee <yejlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 15:03:44 by yejlee            #+#    #+#             */
/*   Updated: 2022/12/21 20:56:06 by yejlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->right_f);
	print_message(philo, get_time() - philo->arg->start_at, TAKE_FORK);
	pthread_mutex_lock(philo->left_f);
	print_message(philo, get_time() - philo->arg->start_at, TAKE_FORK);
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
	pthread_mutex_unlock(philo->right_f);
	pthread_mutex_unlock(philo->left_f);
}

static void	sleep_and_think(t_philo *philo)
{
	long	think_time;
 
	philo->last_sleep = get_time();
	print_message(philo, philo->last_sleep - philo->arg->start_at, SLEEPING);
	while (get_time() < philo->last_sleep + philo->arg->time_to_sleep)
		;
	think_time = get_time() - philo->arg->start_at;
	print_message(philo, think_time, THINKING);
	usleep(200);
}

void	*start_ph(void *thread)
{
	t_philo	*philo;

	philo = (t_philo *)thread;
	if (philo->num % 2 != 0) //변경함
		usleep(philo->arg->time_to_eat * 1000);
	while (!philo->arg->die)
	{
		take_fork(philo);
		eat(philo);
		if (philo->arg->done)
			break ;
		sleep_and_think(philo);
	}
	return (NULL);
}
