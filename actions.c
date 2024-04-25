/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:32:06 by tibarbos          #+#    #+#             */
/*   Updated: 2024/04/25 15:46:42 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
◦ timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died
*/

size_t	get_time(size_t begin)
{
	struct timeval	ct;
	size_t			ms_curr;
	size_t			ms_old;

	ms_old = 0;
	if (begin)
		ms_old = begin;
	gettimeofday(&ct, NULL);
	ms_curr = ct.tv_usec;
	return(ms_curr - ms_old);
}

void	death_status(t_all *all, int ph_nmb)
{
	pthread_mutex_lock(&all->mtx_msg[1]);
	all->death_msg = 1;
	printf("%zu %d died\n", get_time(0), ph_nmb);
	all->death_msg = 0;
	pthread_mutex_unlock(&all->mtx_msg[1]);
}

void	eat_status(t_all *all, int ph_nmb)
{
	if (ph_nmb == 1)
		return ;
	pthread_mutex_lock(&all->mtx_frk[ph_nmb - 1]);
	//all->forks[ph_nmb - 1] = ph_nmb;
	printf("%zu %d has taken a fork", get_time(0), ph_nmb);
	pthread_mutex_lock(&all->mtx_frk[ph_nmb - 2]);
	//all->forks[ph_nmb - 2] = ph_nmb;
	printf("%zu %d has taken a fork", get_time(0), ph_nmb);
	pthread_mutex_lock(&all->mtx_msg[0]);
	/*while (all->forks[ph_nmb - 1] != all->forks[ph_nmb - 2])
	{
		if (all->forks[ph_nmb - 2] == ph_nmb && all->forks[ph_nmb - 2] == ph_nmb)
		{
			printf("%d %d is eating", get_time(NULL), ph_nmb);
			break;
		}
	}*/
	printf("%zu %d is eating", get_time(0), ph_nmb);
	all->people[ph_nmb - 1].last_ate = get_time(0);
	pthread_mutex_unlock(&all->mtx_msg[0]);
	pthread_mutex_unlock(&all->mtx_frk[ph_nmb - 1]);
	pthread_mutex_unlock(&all->mtx_frk[ph_nmb - 2]);
}
/*
se calhar ate posso retirar o while inteiro e deixar so o printf visto
que so chega a esse comando depois de ter ganho as duas locks de mutex

vou meter o alone philo a simplesmente bazar daqui e apenas dormir e
pensar, em vez de ficar aqui impancado porque nao tenho como
interromper este loop

f-1, p1, f0
-.-.-.-.-.-
f 0, p2, f1
f 1, p3, f2
f 2, p4, f3
*/

void	sleep_status(t_all *all, int ph_nmb)
{
	pthread_mutex_lock(&all->mtx_msg[0]);
	while (1)
	{
		if (all->death_msg == 0)
		{
			printf("%zu %d is sleeping", get_time(0), ph_nmb);
			break ;
		}
	}
	pthread_mutex_unlock(&all->mtx_msg[0]);
}

void	think_status(t_all *all, int ph_nmb)
{
	pthread_mutex_lock(&all->mtx_msg[0]);
	while (1)
	{
		if (all->death_msg == 0)
		{
			printf("%zu %d is thinking", get_time(0), ph_nmb);
			break ;
		}
	}
	pthread_mutex_unlock(&all->mtx_msg[0]);
}