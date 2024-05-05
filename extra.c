/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:12:35 by tibarbos          #+#    #+#             */
/*   Updated: 2024/05/05 15:11:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_all(char **av, t_all **all)
{
	if (ft_atoi(av[1]) < 1 || ft_atoi(av[2]) <= 0 || ft_atoi(av[3]) <= 0
		|| ft_atoi(av[4]) <= 0)
		return (0);
	if (av[5] && ft_atoi(av[5]) < 0)
		return (0);
	(*all)->philo_num = ft_atoi(av[1]);
	//(*all)->begin_s = 0;
	//(*all)->begin_us = 0;
	(*all)->time_to_die = ft_atoi(av[2]);
	(*all)->time_to_eat = ft_atoi(av[3]);
	(*all)->time_to_sleep = ft_atoi(av[4]);
	(*all)->eat_no = -2;
	(*all)->global = 0;
	(*all)->start = 0;
	(*all)->go_go_go = 0;
	if (av[5])
		(*all)->eat_no = ft_atoi(av[5]);
	(*all)->mtx_frk = NULL;
	(*all)->forks = malloc((*all)->philo_num * sizeof(int));
	(*all)->death_msg = 0;
	(*all)->mtx_msg = NULL;
	(*all)->people = NULL;
	return (1);
}

int	check_global_death(t_all *all, int source)
{
	int	ret;

	pthread_mutex_lock(&all->mtx_msg[2]);
	if (source == 1)
		all->global = 1;
	ret = all->global;
	pthread_mutex_unlock(&all->mtx_msg[2]);
	return (ret);
}

int	ft_atoi(char *str)
{
	int	atoi;
	int	signal;
	int	i;

	atoi = 0;
	signal = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '	')
		i++;
	if (str[i] == '-')
	{
		i++;
		signal *= -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		atoi = (atoi * 10) + (str[i] - 48);
		i++;
	}
	return (signal * atoi);
}

int	start_race(int mode, t_all *all)
{
	int ret;

	pthread_mutex_lock(&all->mtx_msg[5]);
    if (mode == 1)
        (all->start)++;
	else if (mode == 3)
	{
		all->begin_s = get_time_s();
		all->begin_us = get_time_us();
		all->go_go_go = 1;
	}
    ret = 0;
    if (all->start == all->philo_num && all->go_go_go == 1)
        ret = 1;
    pthread_mutex_unlock(&all->mtx_msg[5]);
    return(ret);
}

/*
- usada na thread creation com o modo 1 (adicionar)
- usada no philo num loop com o modo 2 (wait && observe)

-> (.h) all->start
-> (main) mtx_msg[5] && (main) all->start = 0;
-> (philo) adicao de um usleep(1000) para threads impares para criar delay
-> (philo) adicao da start_race modo 2
-> (philo) adicao da funcao green_light
-> (create_threads) adicao da start_race modo 1

250 (1 maca, snacks)
300.(100) (550).(100)

inside create_threads:
after all thread creation, send a green flag into the start race function
apenas a start race function vai gerir os begin_times, retirar da
create_all
recebe o mode 3, begin time
*/

/*int	my_usleep(size_t time, t_all *all, int nbr)
{
	size_t	i;
	size_t	sleep;

	i = 0;
	sleep = SLEEP_TIMER;
	if (time < SLEEP_MIN_VALUE)
		sleep = SLEEP_MIN_TIMER;
	while (i <= time)
	{
		if (check_hunger(all, nbr) == 1)
			return (0);
		usleep(sleep * 1000);
		i += sleep;
		if (i > time)
		{
			i -= (sleep - 1);
			sleep = 1;
		}
	}
	if (check_hunger(all, nbr) == 1)
		return (0);
	return (1);
}*/
