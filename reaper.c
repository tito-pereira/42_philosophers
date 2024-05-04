/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:27:59 by tibarbos          #+#    #+#             */
/*   Updated: 2024/05/04 19:01:36 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	satisfaction(int mode, t_all *all, int nbr)
{
	int	ret;

	pthread_mutex_lock(&all->mtx_msg[2]);
	ret = 0;
	if (mode == 1)
		all->people[nbr - 1].times_ate += 1;
	if (all->people[nbr - 1].times_ate == all->eat_no)
		ret = 1;
	pthread_mutex_unlock(&all->mtx_msg[2]);
	return (ret);
}

int	full_satisfaction(t_all *all)
{
	int	i;
	int	flag;

	i = 0;
	flag = 1;
	while (++i <= all->philo_num)
	{
		if (satisfaction(2, all, i) == 0)
			flag = 0;
	}
	return (flag);
}

void	*the_reaper(void *void_all)
{
	t_all	*all;
	int		i;

	all = (t_all *)void_all;
	i = 1;
	while (i <= all->philo_num)
	{
		if (satisfaction(2, all, i) == 0)
		{
			if (check_hunger(all, i) == 1)
				break ;
		}
		if (full_satisfaction(all) == 1)
			break ;
		i++;
		if (i == all->philo_num)
			i = 1;
	}
	return (NULL);
}
