/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee <yejlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:18:07 by yejlee            #+#    #+#             */
/*   Updated: 2022/12/13 18:38:34 by yejlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include "arg.h"

typedef struct s_philo
{
	int				num;
	int				status;
	pthread_t		tid;
	pthread_mutex_t	*left_f;
	pthread_mutex_t	*right_f;
	struct t_args	*arg;
}				t_philo;

typedef struct s_args
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_must_eat;
	int				start_time;
	pthread_mutex_t	*fork;
	pthread_mutex_t	messanger;
	pthread_t		monitor;
	t_philo			*philo;
}				t_args;

int		ft_atoi(const char *str);
void	ft_putendl_fd(char *s, int fd);
void	init_all(int ac, char *av[], t_args *arg);

#endif