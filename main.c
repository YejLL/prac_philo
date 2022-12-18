/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee <yejlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 12:47:31 by yejlee            #+#    #+#             */
/*   Updated: 2022/12/18 17:24:19 by yejlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	long long		ms_time;
	struct timeval	time;

	gettimeofday(&time, NULL);
	ms_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ms_time);
}

static void print_message(t_philo *philo, long long time_get, char *str) //상태 메시지 출력
{
	t_args *arg;

	pthread_mutex_lock(&arg->messanger);
	printf("%lldms\t%d\t%s\n", time_get, philo->num, str);
	pthread_mutex_unlock(&arg->messanger);
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

static void check_argu(int ac, t_args *arg)
{
	if (arg->num_philo <= 0)
		ft_putendl_fd("Error in num_philo", 1);
	if (arg->time_to_die <= 0)
		ft_putendl_fd("Error in time_to_die", 1);
	if (arg->time_to_eat <= 0)
		ft_putendl_fd("Error in time_to_eat", 1);
	if (arg->time_to_sleep <= 0)
		ft_putendl_fd("Error in time_to_sleep", 1);
	if (ac == 6 && arg->num_must_eat <= 0)
		ft_putendl_fd("Error in num_must_eat", 1);
}

static void init_all(int ac, char *av[], t_args *arg)
{
	data_set(&arg, ac, &av);
	check_argu(ac, &arg);
	//철학자와 포크 생성, 말록 부분 가져오기 
}

static void init_value(t_args *arg) //value 값 초기화
{
	arg->die = 0;
	arg->fork = 0;
	arg->start_time = 0;
	arg->done = 0;
}

static void check_finish(t_args *arg)
{
	int	i;
	
	while (!arg->done)
	{
		i = -1;
		while (++i < arg->num_philo && !arg->die)
		{
			pthread_mutex_lock(&arg->monitor);
			if (get_time() - arg->philo[i].last_eat > arg->time_to_die)
			{
				print_message(&arg->philo[i], get_time() - arg->time_to_start, DIE);
				arg->die = 1;
			}
			pthread_mutex_unlock(&arg->monitor);
		}
		if (arg->die)
			break ;
		i = 0;
		while(arg->num_must_eat != -1 && i < arg->num_philo 
			&& arg->philo[i].eat_cnt >= arg->num_must_eat)
			i++;
		if (arg->num_philo == i)
			arg->done = 1;
	}
}

static void	*start_routine(void *thread) //스타트 루틴으로 변경 예정
{
	t_philo	*philo;
	t_args 	*arg;

	philo = (t_philo *)thread;
	if (philo->num % 2 != 0)
		usleep(philo->arg->time_to_eat * 1000);
	while (!philo->arg->die) //enum의 DIED 로 변경
	{
		take_fork(philo);
		eat(philo);
		if (philo->arg->done)
			break ;
		sleep_and_think(philo);
	}
}

static void take_fork(t_philo *philo)
{
	if (philo[i].num % 2 == 0)
		pthread_mutex_lock(&philo->arg->fork[philo->left_f]);
	else
		pthread_mutex_lock(&philo->arg->fork[philo->right_f]);
	print_message(philo, get_time() - philo->arg->time_to_start, TAKE_FORK);
	if (philo[i].num % 2 == 0)
		pthread_mutex_lock(&philo->arg->fork[philo->right_f]);
	else
		pthread_mutex_lock(&philo->arg->fork[philo->left_f]);
	print_message(philo, get_time() - philo->arg->time_to_start, TAKE_FORK);
}

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->monitor);
	philo->last_eat = get_time();
	print_message(philo, philo->last_eat - philo->arg->time_to_start, EATING);
	pthread_mutex_unlock(&philo->arg->monitor);
	while (get_time() < philo->last_eat + philo->info->time_to_eat)
		;
	philo->eat_cnt++;
	pthread_mutex_unlock(&philo->arg->fork[philo->left_f]);
	pthread_mutex_unlock(&philo->arg->fork[philo->right_f]);
}

static void sleep_and_think(t_philo *philo)
{
	t_args *arg;
	long	think_time;
	long	sleep_time;

	philo->last_sleep = get_time();
	sleep_time = philo->last_sleep - philo->arg->time_to_start;
	print_message(philo, sleep_time, SLEEPING);
	while (get_time() < philo->last_sleep + philo->arg->time_to_sleep)
		continue;
	think_time = get_time() - philo->arg->time_to_start;
	print_message(philo, think_time, THINKING);
	usleep(200);

}

static void init_mutex(t_args *arg)
{
	int i;

	arg->fork = malloc(sizeof(pthread_mutex_t) * arg->num_philo);
	if (arg->fork == NULL)
	{
		ft_putendl_fd("Error malloc for fork", 1);
		return (NULL);
	}
	i = -1;
	if (++i < arg->num_philo)
	{
		pthread_mutex_init(&arg->fork[i], NULL);
	}
	pthread_mutex_init(&arg->monitor, NULL);
	pthread_mutex_init(&arg->messanger, NULL);

}

static void stock_and_create(t_args *arg)
{
	int	i;
	t_philo *philo;

	i = -1;
	arg = malloc(sizeof(t_args));
	arg->philo = malloc(sizeof(t_philo) * arg->num_philo);
	while (++i < arg->num_philo)
	{
		arg->philo[i].num = i; //0부터 시작하는 방법
		if (phread_create(&arg->philo[i].tid, NULL, start_routine, &arg->philo[i]) < 0)
			ft_putendl_fd("Error in Pthread_create for philosophers, check this", 1);
	}
}

static void free_and_join(t_args *arg)
{
	int i;

	i = -1;
	while (++i < arg->num_philo)
		pthread_join(arg->philo[i].tid, NULL);
	free(arg->philo);
	free(arg);
}
		
int	main(int ac, char *av[])
{
	int		i;
	t_args	*arg;
	t_philo	*philo;
	pthread_mutex_t *fork;

	if (ac != 5 || ac != 6)
	{
		ft_putendl_fd("Error in arguments ac for philosophers.", 1);
		return (-1);

	}
	/*arg = malloc(sizeof(t_args));
	//arg->num_philo = ft_atoi(av[1]);
	arg->philo = malloc(sizeof(t_philo) * arg->num_philo);
	arg->fork = malloc(sizeof(pthread_mutex_t) * arg->num_philo);*/
	init_all(ac, &av, arg);
	stockAndcreate(arg);
	make_fork(&fork);
	freeAndjoin(&arg);
	/*i = -1;
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
			return (signal_error());
	}
	pthread_create((&arg->monitor, NULL, check_ticket, &arg->philo[i]) < 0);
	pthread_detach(&arg->monitor); //모니터 생성한 후 혼자 돌아 다니게 두기*/
	/*i = -1;
	while (++i < arg->num_philo)
		pthread_join(arg->philo[i].tid, NULL);
	free(arg->philo);
	free(arg);*/
	return (0);
}