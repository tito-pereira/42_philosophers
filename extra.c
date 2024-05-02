/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:12:35 by tibarbos          #+#    #+#             */
/*   Updated: 2024/05/02 13:34:18 by tibarbos         ###   ########.fr       */
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
	(*all)->eat_no = -2;
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