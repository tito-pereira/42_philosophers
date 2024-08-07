/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:32:06 by tibarbos          #+#    #+#             */
/*   Updated: 2024/08/02 14:49:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	pick_up_forks(t_all *all, int ph_nmb)
{
	if (check_hunger(2, all, ph_nmb) == 0)
	{
		pthread_mutex_lock(&all->mtx_msg[0]);
		if (check_hunger(2, all, ph_nmb) == 0)
			printf("\033[0;33m%ld %d has taken a fork\033[0m\n", \
			get_time(all), ph_nmb);
		if (check_hunger(2, all, ph_nmb) == 0)
			printf("\033[0;33m%ld %d has taken a fork\033[0m\n", \
			get_time(all), ph_nmb);
		pthread_mutex_unlock(&all->mtx_msg[0]);
	}
}

void	grab_forks(t_all *all, int ph_nmb)
{
	if ((ph_nmb % 2) != 0)
	{
		pthread_mutex_lock(all->people[ph_nmb - 1].f_mtx);
		*(all->people[ph_nmb - 1].f_frk) = ph_nmb;
		pthread_mutex_lock(all->people[ph_nmb - 1].p_mtx);
		*(all->people[ph_nmb - 1].p_frk) = ph_nmb;
	}
	else if ((ph_nmb % 2) == 0)
	{
		pthread_mutex_lock(all->people[ph_nmb - 1].p_mtx);
		*(all->people[ph_nmb - 1].p_frk) = ph_nmb;
		pthread_mutex_lock(all->people[ph_nmb - 1].f_mtx);
		*(all->people[ph_nmb - 1].f_frk) = ph_nmb;
	}
	pick_up_forks(all, ph_nmb);
}

void	return_forks(t_all *all, int ph_nmb)
{
	if ((ph_nmb % 2) != 0)
	{
		*(all->people[ph_nmb - 1].p_frk) = -1;
		pthread_mutex_unlock(all->people[ph_nmb - 1].p_mtx);
		*(all->people[ph_nmb - 1].f_frk) = -1;
		pthread_mutex_unlock(all->people[ph_nmb - 1].f_mtx);
	}
	else if ((ph_nmb % 2) == 0)
	{
		*(all->people[ph_nmb - 1].f_frk) = -1;
		pthread_mutex_unlock(all->people[ph_nmb - 1].f_mtx);
		*(all->people[ph_nmb - 1].p_frk) = -1;
		pthread_mutex_unlock(all->people[ph_nmb - 1].p_mtx);
	}
}

int	eat_status(t_all *all, int ph_nmb)
{
	if (all->philo_num == 1)
		return (0);
	if (check_hunger(2, all, ph_nmb) == 1)
		return (1);
	grab_forks(all, ph_nmb);
	if (check_hunger(2, all, ph_nmb) == 0)
	{
		pthread_mutex_lock(&all->mtx_msg[0]);
		if (check_hunger(2, all, ph_nmb) == 0)
			printf("\033[0;32m%ld %d is eating\033[0m\n", \
			get_time(all), ph_nmb);
		check_hunger(1, all, ph_nmb);
		satisfaction(1, all, ph_nmb);
		pthread_mutex_unlock(&all->mtx_msg[0]);
		usleep(all->time_to_eat * 1000);
	}
	return_forks(all, ph_nmb);
	return (1);
}

void	msg_status(t_all *all, int ph_nmb, int opt)
{
	if (opt == 1 || opt == 2)
	{
		pthread_mutex_lock(&all->mtx_msg[0]);
		if (check_hunger(2, all, ph_nmb) == 0 && opt == 1)
			printf("\033[0;36m%ld %d is sleeping\033[0m\n", \
			get_time(all), ph_nmb);
		if (check_hunger(2, all, ph_nmb) == 0 && opt == 2)
			printf("\033[0;34m%ld %d is thinking\033[0m\n", \
			get_time(all), ph_nmb);
		pthread_mutex_unlock(&all->mtx_msg[0]);
	}
	else if (opt == 3)
	{
		pthread_mutex_lock(&all->mtx_msg[1]);
		if (all->death_msg == 0)
		{
			all->death_msg = 1;
			check_global_death(all, 1);
			printf("\033[0;31m%ld %d died\033[0m\n", get_time(all), ph_nmb);
		}
		pthread_mutex_unlock(&all->mtx_msg[1]);
	}
}
