/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee <yejlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 17:32:01 by yejlee            #+#    #+#             */
/*   Updated: 2022/12/20 19:17:38 by yejlee           ###   ########.fr       */
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
	if (ac == 6 && arg->num_must_eat != 0 && arg->num_must_eat != -1)
		arg->num_must_eat = ft_atoi(av[5]);
	return (0);
}

static int	init_mutex(t_args *arg)
{
	int	i;

	arg->fork = malloc(sizeof(pthread_mutex_t) * arg->num_philo);
	if (arg->fork == NULL)
	{
		ft_putendl_fd("Error malloc for fork", 1);
		return (1);
	}
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
		print_err("error for malloc in arg->philo\n");
	while (++i < arg->num_philo)
	{
		arg->philo[i].num = i + 1;
		arg->philo[i].arg = arg;
	}
	return (0);
}

int	init_all_philo(int ac, char *av[], t_args *arg)
{
	if (check_num(ac, av))
		return (1);
	if (data_set(arg, ac, av))
		return (1);
	if (init_mutex(arg))
		return (1);
	if (init_philo(arg))
		return (1);
	return (0);
}
