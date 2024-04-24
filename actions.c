/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:32:06 by tibarbos          #+#    #+#             */
/*   Updated: 2024/04/24 18:12:53 by tibarbos         ###   ########.fr       */
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
	printf("%d %d died\n", get_time(NULL), ph_nmb);
	all->death_msg = 0;
	pthread_mutex_unlock(&all->mtx_msg[1]);
}

void	eat_status(t_all *all, int ph_nmb)
{
	pthread_mutex_lock(all->forks[ph_nmb - 1]);
	all->forks[ph_nmb - 1] = ph_nmb;
	printf("%d %d has taken a fork", get_time(NULL), ph_nmb);
	pthread_mutex_lock(all->forks[ph_nmb - 2]);
	all->forks[ph_nmb - 2] = ph_nmb;
	printf("%d %d has taken a fork", get_time(NULL), ph_nmb);
	pthread_mutex_lock(&all->mtx_msg[0]);
	//while (forks != ph_nmb), then, break;
	if (all->forks[ph_nmb - 2] == ph_nmb && all->forks[ph_nmb - 2] == ph_nmb)
		printf("%d %d is eating", get_time(NULL), ph_nmb);
	all->people[ph_nmb - 1].last_ate = get_time(NULL);
	pthread_mutex_unlock(&all->mtx_msg[0]);
	pthread_mutex_unlock(all->forks[ph_nmb - 1]);
	pthread_mutex_unlock(all->forks[ph_nmb - 2]);
}
// atualizar o last_ate

void	sleep_status(t_all *all, int ph_nmb)
{
	pthread_mutex_lock(&all->mtx_msg[0]);
	while (1)
	{
		if (all->death_msg == 0)
		{
			printf("%d %d is sleeping", get_time(NULL), ph_nmb);
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
			printf("%d %d is thinking", get_time(NULL), ph_nmb);
			break ;
		}
	}
	pthread_mutex_unlock(&all->mtx_msg[0]);
}