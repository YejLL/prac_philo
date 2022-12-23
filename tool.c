/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee <yejlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:05:44 by yejlee            #+#    #+#             */
/*   Updated: 2022/12/22 20:21:47 by yejlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_num(int ac, char *av[])
{
	int	i;
	int	j;

	i = 0;
	while (++i < ac)
	{
		j = -1;
		while (av[i][++j])
			if (av[i][j] < '0' || av[i][j] > '9')
				return (FALSE);
	}
	return (0);
}

static int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r');
}

int	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long long	n;

	i = 0;
	sign = 1;
	n = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		sign *= -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		if (n * sign > 2147483647)
			return (-1);
		else if (n * sign < -2147483648)
			return (0);
		else
			n = n * 10 + (str[i] - '0');
		i++;
	}
	return (n * sign);
}

/*void	ft_usleep(long long time)
{
	long long	start;

	start = get_time();
	while (get_time() < start + time)
		usleep(10);
}*/

/*void	short_sleep(long int time, t_philo *philo)
{
	long int	start;

	start = get_time();
	while (death_check(philo, 0) == 0)
	{
		if ((get_time() - start) >= time)
			break ;
		if (usleep(50) == -1)
			ft_error(SLEEP_ERROR, philo);
	}
}*/