/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee <yejlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 12:47:31 by yejlee            #+#    #+#             */
/*   Updated: 2022/12/23 12:45:16 by yejlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_finish(t_args *arg)
{
	int	i;

	while (!arg->done)
	{
		i = -1;
		while (++i < arg->num_philo && !arg->die)
		{
			pthread_mutex_lock(&arg->monitor);
			if (get_time() - arg->philo[i].last_eat >= arg->time_to_die)
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
	return (0);
}

int	free_and_join(t_args *arg)
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
	if (pthread_mutex_destroy(&arg->monitor))
		return (1);
	if (pthread_mutex_destroy(&arg->messanger))
		return (1);
	return (0);
}

int	main(int ac, char *av[])
{
	t_args	arg;

	memset(&arg, 0, sizeof(arg));
	if (ac != 5 && ac != 6)
		return (print_err("Error in arguments ac for philosophers."));
	if (init_all_philo(ac, av, &arg))
		return (FALSE);
	if (start_program(&arg))
		return (FALSE);
	if (check_finish(&arg))
		return (FALSE);
	if (free_and_join(&arg))
		return (FALSE);
	return (0);
}
