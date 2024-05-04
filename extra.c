/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:12:35 by tibarbos          #+#    #+#             */
/*   Updated: 2024/05/04 19:40:46 by tibarbos         ###   ########.fr       */
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
	(*all)->begin_s = 0;
	(*all)->begin_us = 0;
	(*all)->time_to_die = ft_atoi(av[2]);
	(*all)->time_to_eat = ft_atoi(av[3]);
	(*all)->time_to_sleep = ft_atoi(av[4]);
	//(*all)->tm_think = (ft_atoi(av[2]) - ft_atoi(av[3]) - ft_atoi(av[4])) / 2;
	(*all)->eat_no = -2;
	(*all)->global = 0;
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
