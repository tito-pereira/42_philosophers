/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:32:06 by tibarbos          #+#    #+#             */
/*   Updated: 2024/04/24 17:42:53 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time(struct timeval *begin)
{
	struct timeval	ct;
	size_t			ms_curr;
	size_t			ms_old;

	ms_old = 0;
	if (begin)
		ms_old = begin->tv_usec;
	gettimeofday(&ct, NULL);
	ms_curr = ct.tv_usec;
	return(ms_curr - ms_old);
}

void	death_status(t_all *all, int ph_nmb)
{
	pthread_mutex_lock(&all->mtx_msg[1]);
	all->death_msg = 1;
	printf("%u Philosopher %d has died.\n", get_time(NULL), ph_nmb);
	all->death_msg = 0;
	pthread_mutex_unlock(&all->mtx_msg[1]);
}

void	eat_status(t_all *all, int ph_nmb)
{
	pthread_mutex_lock(all->forks[ph_nmb - 1]);
	all->forks[ph_nmb - 1] = ph_nmb;
	pthread_mutex_lock(all->forks[ph_nmb - 2]);
	all->forks[ph_nmb - 2] = ph_nmb;
	pthread_mutex_lock(&all->mtx_msg[0]);
	//while (forks != ph_nmb), then, break;
	if (all->forks[ph_nmb - 2] == ph_nmb && all->forks[ph_nmb - 2] == ph_nmb)
		printf("get_timestamp() philo_no eating message");
	pthread_mutex_unlock(&all->mtx_msg[0]);
	pthread_mutex_unlock(all->forks[ph_nmb - 1]);
	pthread_mutex_unlock(all->forks[ph_nmb - 2]);
}

void	sleep_status(t_all *all, int ph_nmb)
{
	pthread_mutex_lock(&all->mtx_msg[0]);
	while (1)
	{
		if (all->death_msg == 0)
		{
			printf("%d Philosopher %d is sleeping.\n", get_time(all), ph_nmb);
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
			printf("%d Philosopher %d is thinking.\n", get_time(), ph_nmb);
			break ;
		}
	}
	pthread_mutex_unlock(&all->mtx_msg[0]);
}