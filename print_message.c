/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee <yejlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 13:31:38 by yejlee            #+#    #+#             */
/*   Updated: 2022/12/21 17:30:30 by yejlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, long long time_get, char *str)
{
	pthread_mutex_lock(&philo->arg->messanger);
	if (!philo->arg->die)
		printf("%lldms\t%d\t%s\n", time_get, philo->num, str);
	pthread_mutex_unlock(&philo->arg->messanger);
}

int	print_err(char *err)
{
	printf("%s\n", err);
	return (FALSE);
}
