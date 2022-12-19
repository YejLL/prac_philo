/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee <yejlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 17:32:01 by yejlee            #+#    #+#             */
/*   Updated: 2022/12/19 18:54:33 by yejlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int data_set(t_args *arg, int ac, char *av[])
{
	arg->num_philo = ft_atoi(av[1]);
	arg->time_to_die = ft_atoi(av[2]);
	arg->time_to_eat = ft_atoi(av[3]);
	arg->time_to_sleep = ft_atoi(av[4]);
	arg->num_must_eat = -1;
	arg->time_to_start = 0;
	arg->done = 0;
	arg->die = 0;
	if (ac == 6 && arg->num_must_eat != 0 && arg->num_must_eat != -1)
		arg->num_must_eat = ft_atoi(av[5]);
	return (0);
}

/*int check_argu(int ac, t_args *arg)
{
	if (arg->num_philo <= 0)
		print_err("Error in num_philo");
	if (arg->time_to_die <= 0)
		print_err("Error in time_to_die");
	if (arg->time_to_eat <= 0)
		print_err("Error in time_to_eat");
	if (arg->time_to_sleep <= 0)
		print_err("Error in time_to_sleep");
	if (ac == 6 && arg->num_must_eat <= 0)
		print_err("Error in num_must_eat");
}*/

/*static void init_value(t_args *arg) //value 값 초기화
{
	arg->die = 0;
	arg->fork = 0;
	arg->time_to_start = 0;
	arg->done = 0;
}*/

int stock_and_create(t_args *arg)
{
	int	i;
	t_philo *philo;

	i = -1;
	arg = malloc(sizeof(t_args));
	arg->philo = malloc(sizeof(t_philo) * arg->num_philo);
	while (++i < arg->num_philo)
	{
		arg->philo[i].num = i + 1;
		if (phread_create(&arg->philo[i].tid, NULL, start_routine, &arg->philo[i]) < 0)
			print_err("Error in Pthread_create for philosophers, check this");
		arg->philo[i].eat_cnt = 0;
		arg->philo[i].last_eat = 0; //스타트 타임이랑 연결할 지 생각
		arg->philo[i].last_sleep = 0;
		arg->philo[i].left_f = i;
		arg->philo[i].right_f = i + 1; //생각해보자
	}
}

int init_mutex(t_args *arg)
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
	
	return (0);
}

int init_all_philo(int ac, char *av[], t_args *arg)
{
	if (check_num == FALSE)
		print_err("Error in arguments\n");
	if (data_set(arg, ac, av))
		return (1);
	if (init_mutex(arg))
		return (1);
	if (stock_and_create(arg))
		return (1);
	return (0);
}