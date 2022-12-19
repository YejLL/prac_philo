/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee <yejlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 15:03:44 by yejlee            #+#    #+#             */
/*   Updated: 2022/12/19 15:30:49 by yejlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	*start_routine(void *thread) //스타트 루틴으로 변경 예정
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