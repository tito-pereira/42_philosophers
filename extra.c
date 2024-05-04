/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:12:35 by tibarbos          #+#    #+#             */
/*   Updated: 2024/05/04 11:28:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_all(char **av, t_all **all)
{
	if (ft_atoi(av[1]) < 1 || ft_atoi(av[2]) <= 0 || ft_atoi(av[3]) <= 0
		|| ft_atoi(av[4]) <= 0)
		return(0);
	if (av[5] && ft_atoi(av[5]) < 0)
		return(0);
	(*all)->philo_num = ft_atoi(av[1]);
	(*all)->begin_s = 0;
	(*all)->begin_us = 0;
	(*all)->time_to_die = ft_atoi(av[2]);
	(*all)->time_to_eat = ft_atoi(av[3]);
	(*all)->time_to_sleep = ft_atoi(av[4]);
	(*all)->tm_think = (ft_atoi(av[2]) - ft_atoi(av[3]) - ft_atoi(av[4])) / 2;
	(*all)->eat_no = -2;
	(*all)->global = 0;
	if (av[5])
		(*all)->eat_no = ft_atoi(av[5]);
	(*all)->mtx_frk = NULL;
	(*all)->forks = malloc((*all)->philo_num * sizeof(int));
	(*all)->death_msg = 0;
	(*all)->mtx_msg = NULL;
	(*all)->people = NULL;
	return(1);
}

int	ft_atoi(char *str)
{
	int	atoi;
	int	signal;
	int	i;

	atoi = 0;
	signal = 1;
	i = 0;
	while(str[i] == ' ' || str[i] == '	')
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
	return(signal * atoi);
}

int	my_usleep(size_t time, t_all *all, int nbr)
{
	size_t	i;

	i = 0;
	if (time < 10)
	{
		while(i <= time)
		{
			if (check_hunger(all, nbr) == 1)
				return(0);
			usleep(1000);
			i++;
		}
	}
	else
	{
		while(i <= time)
		{
			if (check_hunger(all, nbr) == 1)
				return(0);
			usleep(SLEEP_TIMER * 1000);
			i += SLEEP_TIMER;
		}
	}
	if (i > time)
		usleep((i - time) * 1000);
	if (check_hunger(all, nbr) == 1)
        return(0);
	return(1);
}

/*
 < 10 millisseconds condition

if (size_t time < 10)
{
	while(i <= time)
	{
		if (check_hunger(all, nbr) == 1)
        	return(0);
    	usleep(1000);
		i++;
	}
}
*/