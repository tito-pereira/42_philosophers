/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:32:06 by tibarbos          #+#    #+#             */
/*   Updated: 2024/04/24 15:58:37 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time()
{
	ez;
}

void	death_status(t_all *all, int ph_nmb)
{
	pthread_mutex_lock(&all->mtx_msg[1]);
	//all->death_msg = 1;
	printf("%d Philosopher %d has died.\n", get_time(), ph_nmb);
	//all->death_msg = 0;
	pthread_mutex_unlock(&all->mtx_msg[1]);
}

void	eat_status(t_all *all, int ph_nmb)
{
	pthread_mutex_lock(all->forks[ph_nmb - 1]);
	all->forks[ph_nmb - 1] = ph_nmb;
	pthread_mutex_lock(all->forks[ph_nmb - 2]);
	all->forks[ph_nmb - 2] = ph_nmb;
	pthread_mutex_lock(&all->mtx_msg[0]);
	if (fork_left == philo_no && fork_right == philo_no)
		printf("get_timestamp() philo_no eating message");
	pthread_mutex_unlock(&all->mtx_msg[0]);
	pthread_mutex_unlock(fork_left);
	pthread_mutex_unlock(fork_right);
}

void	sleep_status(t_all *all, int ph_nmb)
{
	pthread_mutex_lock(&all->mtx_msg[0]);
	while (1)
	{
		if (death_msg == 0)
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