/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejlee <yejlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 12:47:31 by yejlee            #+#    #+#             */
/*   Updated: 2022/12/13 18:47:41 by yejlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void print_message(t_philo *philo, char *str) //상태 메시지 출력
{
	t_args *arg;

	pthread_mutex_lock(&arg->messanger);
	printf("%lld\t%d\t%s\n", ms_time, philo->num, str);
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

/*static void print_sleep_think(t_philo *philo, int status) //랜덤으로 자거나 먹는 방법 사용
{
	if (status == SLEEP)
		printf("%d is sleeping\n", philo->num);
	if (status == THINK)
		printf("%d is thinking\n", philo->num);
}*/ //고민중

static void	*start(void *thread) //스타트 루틴으로 변경 예정
{
	int i;
	t_philo	*philo;
	t_args 	*arg;

	i = -1;
	philo = (t_philo *)thread;
	while (++i != arg->die)
	{
		take_fork();
		eat();
		printf("[philo %d] and tid: [%ld]\n", philo->num, philo->tid);
	}
}

static void	eat(t_philo *philo)
{
	t_args *arg;
	
	take_fork();
	print_message(eat);
	pthread_mutex_unlock(&philo->left_f);
	pthread_mutex_unlock(&philo->right_f);
}

/*static void	take_fork(t_philo *philo)
{
	pthread_mutex_lock

}*/

static void *check_ticket(void *monitor, int n) //철학자들이 젓가락을 쥐려면 허락을 받아야 함.
{
	t_philo *philo;
	t_args *arg;
	
	arg->monitor = (t_philo *)monitor;
	if (arg->philo[n].num % 2 == 0) //짝수일 경우
	{
		pthread_mutex_lock(&philo->left_f);
		pthread_mutex_lock(&philo->right_f);
		print_message();//00가 포크 잡음
	}
	else
	{
		pthread_mutex_lock(&philo->right_f);
		pthread_mutex_lock(&philo->left_f);
		print_message();
		//홀수의 경우 오른쪽 포크 먼저 쥐긴
	}
}

static void *make_fork(pthread_mutex_t *fork) //포크 만들기
{
	int	i;
	t_args *args;
	
	i = -1;
	if (++i < args->num_philo)
	{
		pthread_mutex_init(&fork[i], NULL);
	}
}

static void stockAndcreate(t_args *arg)
{
	int	i;
	t_philo *philo;

	i = -1;
	arg = malloc(sizeof(t_args));
	arg->philo = malloc(sizeof(t_philo) * arg->num_philo);
	arg->fork = malloc(sizeof(pthread_mutex_t) * arg->num_philo);
	while (++i < arg->num_philo)
	{
		arg->philo[i].num = i;
		if (phread_create(&arg->philo[i].tid, NULL, start, &arg->philo[i]) < 0)
			return (FALSE);
	}
	if (pthread_create(&arg->monitor, NULL, check_ticket, &arg->philo[i]) < 0); //모니터 생성..
		return (FALSE);
	pthread_detach(&arg->monitor);
}

static void freeAndjoin(t_args *arg)
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

	/*if (ac != 5 || ac != 6)
		signal_error();*/
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

/*개선 사항
1. 먹기 잠자기 생각하기 만들기.
2. 시간 체킹 함수 만들기.
3. 모니터링 더 자세히 알아보기.