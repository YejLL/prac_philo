/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee <yejlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 17:32:01 by yejlee            #+#    #+#             */
/*   Updated: 2022/12/23 11:41:41 by yejlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	data_set(t_args *arg, int ac, char *av[])
{
	arg->num_philo = ft_atoi(av[1]);
	arg->time_to_die = ft_atoi(av[2]);
	arg->time_to_eat = ft_atoi(av[3]);
	arg->time_to_sleep = ft_atoi(av[4]);
	arg->num_must_eat = -1;
	arg->start_at = 0;
	arg->done = 0;
	if (ac == 6)
		arg->num_must_eat = ft_atoi(av[5]);
	return (0);
}

static int	init_mutex(t_args *arg)
{
	int	i;

	arg->fork = malloc(sizeof(pthread_mutex_t) * arg->num_philo);
	if (arg->fork == NULL)
		print_err("ERROR IN MALLOC ARG->FORK");
	i = -1;
	if (++i < arg->num_philo)
	{
		pthread_mutex_init(&arg->fork[i], NULL);
	}
	pthread_mutex_init(&arg->monitor, NULL);
	pthread_mutex_init(&arg->messanger, NULL);
	return (0);
}

static int	init_philo(t_args *arg)
{
	int	i;

	i = -1;
	arg->philo = malloc(sizeof(t_philo) * arg->num_philo);
	if (arg->philo == NULL)
		print_err("ERROR IN MALLOC ARG->PHILO");
	while (++i < arg->num_philo)
	{
		arg->philo[i].num = i + 1;
		arg->philo[i].left_f = i;
		arg->philo[i].right_f = ((i + 1) % arg->num_philo);
		arg->philo[i].arg = arg;
	}
	return (0);
}

int	init_all_philo(int ac, char *av[], t_args *arg)
{
	if (check_num(ac, av))
		return (FALSE);
	if (data_set(arg, ac, av))
		return (FALSE);
	if (init_mutex(arg))
		return (FALSE);
	if (init_philo(arg))
		return (FALSE);
	return (0);
}
