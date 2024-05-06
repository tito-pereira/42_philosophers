/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:12:35 by tibarbos          #+#    #+#             */
/*   Updated: 2024/05/06 11:00:38 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_all(char **av, t_all **all)
{
	if (ft_atoi(av[1]) < 1 || ft_atoi(av[2]) <= 0 || ft_atoi(av[3]) <= 0
		|| ft_atoi(av[4]) <= 0)
		return (0);
	if (av[5] && ft_atoi(av[5]) <= 0)
		return (0);
	(*all)->philo_num = ft_atoi(av[1]);
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

int	check_hunger(int mode, t_all *all, int nbr)
{
	long	hunger;
	int		ret;

	ret = 0;
	pthread_mutex_lock(&all->mtx_msg[4]);
	if (mode == 1)
		all->people[nbr - 1].last_ate = get_time(all);
	else if (mode == 2)
	{
		hunger = get_time(all) - all->people[nbr - 1].last_ate;
		if (hunger > 0 && (size_t)hunger > all->time_to_die)
		{
			msg_status(all, nbr, 3);
			ret = 1;
		}
	}
	pthread_mutex_unlock(&all->mtx_msg[4]);
	if (check_global_death(all, 2) == 1 || ret == 1)
		return (1);
	return (0);
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
	int	ret;

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
	return (ret);
}
