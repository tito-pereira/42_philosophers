/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:32:06 by tibarbos          #+#    #+#             */
/*   Updated: 2024/05/02 12:07:03 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat_status(t_all *all, int ph_nmb)
{
	if (all->philo_num == 1)
		return ;
	while (1)
	{
		if (all->death_msg == 1)
			break ;
		pthread_mutex_lock(all->people[ph_nmb - 1].f_mtx);
		*(all->people[ph_nmb - 1].f_frk) = ph_nmb;
		if (*(all->people[ph_nmb - 1].p_frk) == -1)
		{
			pthread_mutex_lock(all->people[ph_nmb - 1].p_mtx);
			*(all->people[ph_nmb - 1].p_frk) = ph_nmb;
			if (all->death_msg == 0)
			{
				pthread_mutex_lock(&all->mtx_msg[0]);
				printf("\033[0;33m%ld %d has taken a fork\033[0m\n", get_time(all), ph_nmb);
				printf("\033[0;33m%ld %d has taken a fork\033[0m\n", get_time(all), ph_nmb);
				pthread_mutex_unlock(&all->mtx_msg[0]);
			}
			else
			{
				*(all->people[ph_nmb - 1].f_frk) = -1;
				pthread_mutex_unlock(all->people[ph_nmb - 1].f_mtx);
			}
		}
		else
		{
			*(all->people[ph_nmb - 1].f_frk) = -1;
			pthread_mutex_unlock(all->people[ph_nmb - 1].f_mtx);
			continue ;
		}
		if (all->death_msg == 0)
		{
			pthread_mutex_lock(&all->mtx_msg[0]);
			if (all->death_msg == 0)
				printf("\033[0;32m%ld %d is eating\033[0m\n", get_time(all), ph_nmb);
			all->people[ph_nmb - 1].last_ate = get_time(all);
			pthread_mutex_unlock(&all->mtx_msg[0]);
			usleep(all->time_to_eat * 1000);
		}
		*(all->people[ph_nmb - 1].f_frk) = -1;
		pthread_mutex_unlock(all->people[ph_nmb - 1].f_mtx);
		*(all->people[ph_nmb - 1].p_frk) = -1;
		pthread_mutex_unlock(all->people[ph_nmb - 1].p_mtx);
		break ;
	}
}

void	msg_status(t_all *all, int ph_nmb, int opt)
{
	if (opt == 1 || opt == 2) // sleep
	{
		pthread_mutex_lock(&all->mtx_msg[0]);
		if (all->death_msg == 0 && opt == 1) //sleep
			printf("\033[0;36m%ld %d is sleeping\033[0m\n", get_time(all), ph_nmb);
		if (all->death_msg == 0 && opt == 2) //think
			printf("\033[0;34m%ld %d is thinking\033[0m\n", get_time(all), ph_nmb);
		pthread_mutex_unlock(&all->mtx_msg[0]);
	}
	else if (opt == 3) // die
	{
		pthread_mutex_lock(&all->mtx_msg[1]);
		if (all->death_msg == 0)
		{
			all->death_msg = 1;
			printf("\033[0;31m%ld %d died\033[0m\n", get_time(all), ph_nmb);
		}
		pthread_mutex_unlock(&all->mtx_msg[1]);
	}
}

/*
	if (opt == 1) // sleep
	{
		pthread_mutex_lock(&all->mtx_msg[0]);
		if (all->death_msg == 0)
			printf("\033[0;36m%ld %d is sleeping\033[0m\n", get_time(all), ph_nmb);
		pthread_mutex_unlock(&all->mtx_msg[0]);
	}
	else if (opt == 2) // think
	{
		pthread_mutex_lock(&all->mtx_msg[0]);
		if (all->death_msg == 0)
			printf("\033[0;34m%ld %d is thinking\033[0m\n", get_time(all), ph_nmb);
		pthread_mutex_unlock(&all->mtx_msg[0]);
	}

void	sleep_status(t_all *all, int ph_nmb)
{
	pthread_mutex_lock(&all->mtx_msg[0]);
	if (all->death_msg == 0)
		printf("\033[0;36m%ld %d is sleeping\033[0m\n", get_time(all), ph_nmb);
	pthread_mutex_unlock(&all->mtx_msg[0]);
}

void	think_status(t_all *all, int ph_nmb)
{
	pthread_mutex_lock(&all->mtx_msg[0]);
	if (all->death_msg == 0)
		printf("\033[0;34m%ld %d is thinking\033[0m\n", get_time(all), ph_nmb);
	pthread_mutex_unlock(&all->mtx_msg[0]);
}

void	death_status(t_all *all, int ph_nmb)
{
	if (all->death_msg == 0)
	{
		pthread_mutex_lock(&all->mtx_msg[1]);
		if (all->death_msg == 0) //verificacao extra mutex pode demorar
		{
			all->death_msg = 1;
			printf("\033[0;31m%ld %d died\033[0m\n", get_time(all), ph_nmb);
		}
		pthread_mutex_unlock(&all->mtx_msg[1]);
	}
}
*/