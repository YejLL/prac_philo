/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee <yejlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 13:31:38 by yejlee            #+#    #+#             */
/*   Updated: 2022/12/19 13:49:49 by yejlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_message(t_philo *philo, long long time_get, char *str)
{
	t_args *arg;

	pthread_mutex_lock(&arg->messanger);
	if (!philo->arg->die)
		printf("%lldms\t%d\t%s\n", time_get, philo->num, str);
	pthread_mutex_unlock(&arg->messanger);
}