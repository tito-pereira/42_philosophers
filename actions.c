/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:32:06 by tibarbos          #+#    #+#             */
/*   Updated: 2024/04/27 19:06:14 by marvin           ###   ########.fr       */
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

size_t	get_time_sub(size_t begin)
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

void	death_status(t_all *all, int ph_nmb)
{
	pthread_mutex_lock(&all->mtx_msg[1]);
	all->death_msg = 1;
	printf("%ld %d died\n", get_time(all), ph_nmb);
	all->death_msg = 0;
	pthread_mutex_unlock(&all->mtx_msg[1]);
}

void	eat_status(t_all *all, int ph_nmb)
{
	size_t	last_ate;

	last_ate = all->people[ph_nmb - 1].last_ate;
	if (all->philo_num == 1)
		return ;
	while (1)
	{
		pthread_mutex_lock(&all->mtx_frk[ph_nmb - 1]);
		all->forks[ph_nmb - 1] = ph_nmb;
		if (all->forks[ph_nmb - 2] == -1)
		{
			pthread_mutex_lock(&all->mtx_frk[ph_nmb - 2]);
			all->forks[ph_nmb - 2] = ph_nmb;
			printf("%ld %d has taken a fork\n", get_time(all), ph_nmb);
			printf("%ld %d has taken a fork\n", get_time(all), ph_nmb);
		}
		else
		{
			printf("Philosopher [%d] is retrying to eat.\n", ph_nmb);
			all->forks[ph_nmb - 1] = -1;
			pthread_mutex_unlock(&all->mtx_frk[ph_nmb - 1]);
			continue;
		}
		pthread_mutex_lock(&all->mtx_msg[0]);
		printf("%ld %d is eating\n", get_time(0), ph_nmb);
		all->people[ph_nmb - 1].last_ate = (get_time(all) - last_ate);
		printf("Philosopher [%d] last ate was: %ld;\n", ph_nmb, all->people[ph_nmb - 1].last_ate);
		pthread_mutex_unlock(&all->mtx_msg[0]);
		all->forks[ph_nmb - 1] = -1;
		pthread_mutex_unlock(&all->mtx_frk[ph_nmb - 1]);
		all->forks[ph_nmb - 2] = -1;
		pthread_mutex_unlock(&all->mtx_frk[ph_nmb - 2]);
		break ;
	}
}
/*
vou meter o alone philo a simplesmente bazar daqui e apenas dormir e
pensar, em vez de ficar aqui impancado porque nao tenho como
interromper este loop

filosofo 1
garfo[0]
garfo[-1]
e se eu criar previous / following fork, dentro de cada pessoa ?
um pointer para o actual forks[] da all struct

e na eat_status, em vez de usar all->forks[-1 e -2], uso
all->people[ph_nmb - 1]->p_frk = all->forks[ph_nmb - 2];
all->people[ph_nmb - 1]->f_frk = all->forks[ph_nmb - 1];
e se calhar tambem um mutex *p e *f
all->people[ph_nmb - 1]->p_mtx = all->mtx_frk[ph_nmb - 2];
all->people[ph_nmb - 1]->f_mtx = all->mtx_frk[ph_nmb - 1];

f-1, p1, f0
-.-.-.-.-.-
f 0, p2, f1
f 1, p3, f2
f 2, p4, f3
*/

void	sleep_status(t_all *all, int ph_nmb)
{
	pthread_mutex_lock(&all->mtx_msg[0]);
	if (all->death_msg == 0)
		printf("%ld %d is sleeping\n", get_time(all), ph_nmb);
	pthread_mutex_unlock(&all->mtx_msg[0]);
}
// tirei os while(1) porque eu quero q o programa acabe e nao
// fique ali à espera

void	think_status(t_all *all, int ph_nmb)
{
	pthread_mutex_lock(&all->mtx_msg[0]);
	if (all->death_msg == 0)
		printf("%ld %d is thinking\n", get_time(all), ph_nmb);
	pthread_mutex_unlock(&all->mtx_msg[0]);
}

/*
eating:
while (all->forks[ph_nmb - 1] != all->forks[ph_nmb - 2])
{
	if (all->forks[ph_nmb - 2] == ph_nmb && all->forks[ph_nmb - 2] == ph_nmb)
	{
		printf("%d %d is eating", get_time(NULL), ph_nmb);
		break;
	}
}*/