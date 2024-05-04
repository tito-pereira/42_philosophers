/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trylocks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:27:59 by tibarbos          #+#    #+#             */
/*   Updated: 2024/05/04 18:11:49 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*int	grab_forks(t_all *all, int ph_nmb)
{
	if ((ph_nmb % 2) != 0)
	{
		if (my_trylock(all->people[ph_nmb - 1].f_mtx) == 0)
            return(0);
		*(all->people[ph_nmb - 1].f_frk) = ph_nmb;
		if (pthread_mutex_lock(all->people[ph_nmb - 1].p_mtx) == 0)
        {
            *(all->people[ph_nmb - 1].f_frk) = ph_nmb;
            pthread_mutex_unlock(all->people[ph_nmb - 1].f_mtx);
            return(0);
        }
		*(all->people[ph_nmb - 1].p_frk) = ph_nmb;
	}
	else if ((ph_nmb % 2) == 0)
	{
		pthread_mutex_lock(all->people[ph_nmb - 1].p_mtx);
		*(all->people[ph_nmb - 1].p_frk) = ph_nmb;
		pthread_mutex_lock(all->people[ph_nmb - 1].f_mtx);
		*(all->people[ph_nmb - 1].f_frk) = ph_nmb;
	}
    return(1);
}*/

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
	return(ret);
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
	return(flag);
}

void	*the_reaper(void *void_all)
{
	t_all	*all;
	int		i;
	
	all = (t_all *)void_all;
	i = 1;
	//printf("inside the reaper thread in %zu\n", get_time(all));
	while (i <= all->philo_num)
	{
		if (satisfaction(2, all, i) == 0)
		{
			if (check_hunger(all, i) == 1)
				break;
		}
		if (full_satisfaction(all) == 1)
			break ;
		i++;
		if (i == all->philo_num)
			i = 1;
	}
	return(NULL);
}

/*
ja n me lembro onde ia, vamos testando

incorporar a full satisfaction na reaper main loop

(V) -> satisfaction() functio
(V) -> mutex msg[4] (main)
(V) -> t_person; (philo.h, main)
int	times_ate = 0;
(V) -> (a cada eat, individual mutex protected) (actions)
all->people[ph_nmb - 1].times_ate ++;
ou
satisfaction(mode 1, all, nbr)
(V) -> the reaper checking satisfaction (trylocks)

(1)
if satisfaction(mode 2) == 0 (not satisfied), check hunger
full satisfaction end condition (a cada loop?)
---
(2)
if not satisfied, check hunger, flag active
if flag inactive
	global satisfaction, e acaba a funcao
else
	reset flag, i = 1
*/