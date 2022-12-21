/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee <yejlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 12:47:31 by yejlee            #+#    #+#             */
/*   Updated: 2022/12/21 18:00:58 by yejlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char *av[])
{
	t_args	arg;

	memset(&arg, 0, sizeof(arg));
	if (ac != 5 && ac != 6)
		return (print_err("Error in arguments ac for philosophers."));
	if (init_all_philo(ac, av, &arg))
		return (FALSE);
	if (start_program(&arg))
		return (FALSE);
	return (0);
}
