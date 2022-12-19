/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee <yejlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 13:51:19 by yejlee            #+#    #+#             */
/*   Updated: 2022/12/19 15:02:57 by yejlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void check_finish(t_args *arg)
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