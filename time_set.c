/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee <yejlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 13:30:33 by yejlee            #+#    #+#             */
/*   Updated: 2022/12/23 11:18:57 by yejlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	long long		ms_time;
	struct timeval	time;

	ms_time = 0;
	if (gettimeofday(&time, NULL) == -1)
		return (print_err("ERROR IN TIME"));
	ms_time = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	return (ms_time);
}

long long	timed_now(struct timeval *start, struct timeval *end)
{
	long	diff;

	diff = (end->tv_sec - start->tv_sec) * 1e3 + \
				(end->tv_usec - start->tv_usec) / 1e3;
	return (diff);
}
