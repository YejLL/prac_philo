/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee <yejlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 13:51:19 by yejlee            #+#    #+#             */
/*   Updated: 2022/12/21 18:19:57 by yejlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_finish(t_args *arg)
{
	int	i;

	while (!arg->done)
	{
		i = -1;
		while (++i < arg->num_philo && !arg->die)
		{
			pthread_mutex_lock(&arg->monitor);
			if (get_time() - arg->philo[i].last_eat > arg->time_to_die) //> 였음
			{
				print_message(&arg->philo[i], get_time() \
						- arg->start_at, DIE);
				arg->die = 1;
			}
			pthread_mutex_unlock(&arg->monitor);
		}
		if (arg->die)
			break ;
		i = 0;
		while (arg->num_must_eat != -1 && i < arg->num_philo \
				&& arg->philo[i].eat_cnt >= arg->num_must_eat)
			i++;
		if (arg->num_philo == i)
			arg->done = 1;
	}
}

static void	free_and_join(t_args *arg)
{
	int	i;

	i = -1;
	if (arg->num_philo == 1)
		pthread_detach(arg->philo[0].tid);
	while (++i < arg->num_philo)
		pthread_join(arg->philo[i].tid, NULL);
	free(arg->philo);
	i = -1;
	while (++i < arg->num_philo)
		pthread_mutex_destroy(&arg->fork[i]);
	free(arg->fork);
	pthread_mutex_destroy(&arg->monitor);
	pthread_mutex_destroy(&arg->messanger);
}

int	start_program(t_args *arg)
{
	int	i;

	arg->start_at = get_time();
	i = -1;
	while (++i < arg->num_philo)
	{
		arg->philo[i].last_eat = arg->start_at;
		arg->philo[i].last_sleep = arg->start_at;
		arg->philo[i].eat_cnt = 0;
		if (pthread_create(&arg->philo[i].tid, NULL, start_ph, &arg->philo[i]))
			return (print_err("ERROR IN CREATE\n"));
	}
	check_finish(arg);
	free_and_join(arg);
	return (0);
}
