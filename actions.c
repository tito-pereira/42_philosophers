/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:32:06 by tibarbos          #+#    #+#             */
/*   Updated: 2024/04/26 14:57:13 by marvin           ###   ########.fr       */
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

// t_all *all, get_time_us
size_t	get_time(size_t begin)
{
	struct timeval	ct;
	struct timezone	tz;
	size_t			us_curr;
	size_t			us_old;

	us_old = 0;
	if (begin)
		us_old = begin;
	gettimeofday(&ct, &tz);
	us_curr = ct.tv_usec;
	return((us_curr - us_old) / 1000);
}

/*
size_t	get_time(size_t begin)
{
	struct timeval	ct;
	struct timezone	tz;
	size_t			us_curr;
	size_t			us_old;

	us_old = 0;
	if (begin)
		us_old = begin;
	gettimeofday(&ct, &tz);
	us_curr = ct.tv_usec;
	return((us_curr - us_old) / 1000);
}

size_t	get_time(size_t begin)
{
	struct timeval	ct;
	struct timezone	tz;
	size_t			us_curr;
	size_t			us_old;

	us_old = 0;
	if (begin)
		us_old = begin;
	gettimeofday(&ct, &tz);
	us_curr = ct.tv_usec;
	return((us_curr - us_old) / 1000);
}

int	get_time_tt(t_all *all)
{
	int	us_curr;
	int	s_curr;
	
	s_curr = get_time_s(void);
	us_curr = get_time_us(void);
	if (s_curr > all->begin_s)
		diff_s = diff(s_curr, all->begin_s);
	else
		diff_s = diff(all->begin_s, s_curr);
	diff_s = diff_s * 1000;
	if (us_curr > all->begin_s)
		diff_us = diff(us_curr, all->begin_us);
	else
		diff_us = diff(all->begin_us, us_curr);
	diff_s = diff_s / 1000;
	return ((all->min_passed * 1000) + diff_s + diff_us);
}

void	*timetable(void *all)
{
	struct timeval	ct;
	struct timezone	tz;
	int				sec;
	
	while (1)
	{
		gettimeofday(&ct, &tz);
		sec = ct.tv_sec;
		if (sec == 60)
			(all->min_passed)++;
	}
	return(NULL);
}*/

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
	printf("%zu %d has taken a fork\n", get_time(0), ph_nmb);
	pthread_mutex_lock(&all->mtx_frk[ph_nmb - 2]);
	//all->forks[ph_nmb - 2] = ph_nmb;
	printf("%zu %d has taken a fork\n", get_time(0), ph_nmb);
	pthread_mutex_lock(&all->mtx_msg[0]);
	printf("%zu %d is eating\n", get_time(0), ph_nmb);
	all->people[ph_nmb - 1].last_ate = (get_time(0) - all->begin_time);
	pthread_mutex_unlock(&all->mtx_msg[0]);
	pthread_mutex_unlock(&all->mtx_frk[ph_nmb - 1]);
	pthread_mutex_unlock(&all->mtx_frk[ph_nmb - 2]);
}
/*
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
			printf("%zu %d is sleeping\n", get_time(0), ph_nmb);
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
			printf("%zu %d is thinking\n", get_time(0), ph_nmb);
			break ;
		}
	}
	pthread_mutex_unlock(&all->mtx_msg[0]);
}

/*while (all->forks[ph_nmb - 1] != all->forks[ph_nmb - 2])
{
	if (all->forks[ph_nmb - 2] == ph_nmb && all->forks[ph_nmb - 2] == ph_nmb)
	{
		printf("%d %d is eating", get_time(NULL), ph_nmb);
		break;
	}
}*/