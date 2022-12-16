/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee <yejlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:25:02 by yejlee            #+#    #+#             */
/*   Updated: 2022/12/16 17:07:36 by yejlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARG_H
# define ARG_H
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define TAKE_FORK "has taken a fork"
# define DIE "died"

# include "philo.h"

typedef enum e_status
{
	SLEEP = 2,
	THINK = 3,
	EAT = 4,
	DIED = 5,
	TAKE = 6
}			t_status;

typedef enum e_bool
{
	TRUE = 0,
	FALSE = -1	
}			t_bool;

#endif
