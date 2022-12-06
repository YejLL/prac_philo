/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee <yejlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 12:47:31 by yejlee            #+#    #+#             */
/*   Updated: 2022/12/06 17:34:36 by yejlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void signal_error(void)
{
	printf("Error!\n");
	exit (1);
}

static void data_set(t_args *arg, int ac, char *av[])
{
	arg->num_philo = ft_atoi(av[1]);
	arg->time_to_die = ft_atoi(av[2]);
	arg->time_to_eat = ft_atoi(av[3]);
	arg->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6 && arg->num_must_eat != 0)
		arg->num_must_eat = ft_atoi(av[5]);
}

static void check_argu(t_args *arg)
{
	if (arg->num_philo < 0)
		ft_putendl_fd("Error in num_philo", 1);
	if (arg->time_to_die < 0)
		ft_putendl_fd("Error in time_to_die", 1);
	if (arg->time_to_eat < 0)
		ft_putendl_fd("Error in time_to_eat", 1);
	if (arg->time_to_sleep < 0)
		ft_putendl_fd("Error in time_to_sleep", 1);
	/*if (arg->num_must_eat < 0)
		ft_putendl_fd("Error in num_must_eat", 1);*/ //어떻게 처리할 지 생각중
}

static void print_sleep_think(t_philo *philo, int status) //랜덤으로 자거나 먹는 방법 사용
{
	if (status == SLEEP)
		printf("%d is sleeping\n", philo->num);
	if (status == THINK)
		printf("%d is thinking\n", philo->num);
}

static void	*act(void *thread) //스타트 루틴으로 변경 예정
{
	t_philo	*philo;
	pthread_mutex_t pause;

	philo = (t_philo *)thread;
	pthread_mutex_lock(&pause);
	printf("[philo %d] and tid: [%ld]\n", philo->num, philo->tid);
	printf("Done\n");
	pthread_mutex_unlock(&pause);
}

static void *take_fork()
{

}

static void *check_ticket(void *monitor, int n) //철학자들이 젓가락을 쥐려면 허락을 받아야 함.
{
	t_philo *philo;
	t_args *arg;
	
	philo = (t_philo *)monitor;
	if (arg->philo[n].num % 2 == 0) //짝수일 경우
	{
		take_fork();
		//기다리기 or 왼쪽 포크 쥐기

	}
	else
	{
		print_sleep_think(philo, );
		//홀수의 경우 오른쪽 포크 먼저 쥐긴
	}
}

static void *make_fork(pthread_mutex_t *fork) //포크 만들기
{
	t_args *args;
	int i;
	
	i = -1;
	if (++i < args->num_philo)
	{
		pthread_mutex_init(&fork[i], NULL);
	}
}

int	main(int ac, char *av[])
{
	int		i;
	int 	monitor;
	t_args	*arg;
	t_philo	*philo;
	pthread_mutex_t *fork;

	/*if (ac != 5 || ac != 6)
		signal_error();*/
	arg = malloc(sizeof(t_args));
	//arg->num_philo = ft_atoi(av[1]);
	arg->philo = malloc(sizeof(t_philo) * arg->num_philo);
	arg->fork = malloc(sizeof(pthread_mutex_t) * arg->num_philo);
	data_set(&arg, ac, &av);
	check_argu(&arg);
	make_fork(&fork);
	i = -1;
	while (++i < arg->num_philo)
	{
		arg->philo[i].num = i;
	}
	i = -1;
	while (++i < arg->num_philo)
	{
		if (pthread_create(&arg->philo[i].tid, NULL, act, &arg->philo[i]) < 0)
			return (signal_error());
		/*if (pthread_create(&arg->fork[i], NULL, 함수, &arg->fork[i]) < 0) //포크 생성
			return (signal_error());*/
	}
	pthread_create(&monitor, NULL, check_ticket, &arg->philo[i]);//모니터 생성할 예정
	i = -1;
	while (++i < arg->num_philo)
		pthread_join(arg->philo[i].tid, NULL);
	free(arg->philo);
	free(arg);
	return (0);
}