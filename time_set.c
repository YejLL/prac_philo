/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee <yejlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 13:30:33 by yejlee            #+#    #+#             */
/*   Updated: 2022/12/20 19:21:19 by yejlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	long long		ms_time;
	struct timeval	time;

	gettimeofday(&time, NULL);
	ms_time = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	return (ms_time);
}
