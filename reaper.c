/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:27:59 by tibarbos          #+#    #+#             */
/*   Updated: 2024/05/05 13:48:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	satisfaction(int mode, t_all *all, int nbr)
{
	int	ret;

	pthread_mutex_lock(&all->mtx_msg[3]);
	ret = 0;
	if (mode == 1)
		all->people[nbr - 1].times_ate += 1;
	if (all->people[nbr - 1].times_ate == all->eat_no)
		ret = 1;
	pthread_mutex_unlock(&all->mtx_msg[3]);
	return (ret);
}

/*int	full_satisfaction(t_all *all)
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
}*/

void	*the_reaper(void *void_all)
{
	t_all	*all;
	int		i;
	int		all_full;

	all = (t_all *)void_all;
	i = 1;
	all_full = 1;
	while (i <= all->philo_num)
	{
		if (satisfaction(2, all, i) == 0)
		{
			all_full = 0;
			if (check_hunger(2, all, i) == 1)
				break ;
		}
		//if (full_satisfaction(all) == 1)
			//break ;
		i++;
		if (i == all->philo_num)
		{
			if (all_full == 1)
				break;
			i = 1;
			all_full = 1;
		}
	}
	return (NULL);
}
