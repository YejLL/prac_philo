/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee <yejlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:18:07 by yejlee            #+#    #+#             */
/*   Updated: 2022/12/21 20:56:35 by yejlee           ###   ########.fr       */
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
	int				eat_cnt;
	long long		last_eat;
	long long		last_sleep;
	pthread_mutex_t	*left_f;
	pthread_mutex_t	*right_f;
	pthread_t		tid;
	struct s_args	*arg;
}				t_philo;

typedef struct s_args
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_must_eat;
	long long		start_at;
	int				die;
	int				done;
	pthread_mutex_t	*fork;
	pthread_mutex_t	messanger;
	pthread_mutex_t	monitor;
	t_philo			*philo;
}				t_args;

int			ft_atoi(const char *str);
int			print_err(char *err);
int			check_num(int ac, char *av[]);
int			start_program(t_args *arg);
int			init_all_philo(int ac, char *av[], t_args *arg);
int			check_num(int ac, char *av[]);
long long	get_time(void);
void		*start_ph(void *thread);
void		ft_putendl_fd(char *s, int fd);
void		print_message(t_philo *philo, long long time_get, char *str);

#endif
