/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:32:06 by tibarbos          #+#    #+#             */
/*   Updated: 2024/04/29 15:47:54 by tibarbos         ###   ########.fr       */
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
	if (all->death_msg == 0)
	{
		pthread_mutex_lock(&all->mtx_msg[1]);
		all->death_msg = 1;
		printf("\033[0;31m%ld %d died\033[0m\n", get_time(all), ph_nmb);
		//all->death_msg = 0;
		pthread_mutex_unlock(&all->mtx_msg[1]);
	}
}

void	eat_status(t_all *all, int ph_nmb)
{
	//printf("Philosopher [%d] inside eating actions.\n", ph_nmb);
	if (all->philo_num == 1)
		return ;
	while (1)
	{
		if (all->death_msg == 1)
			break ;
		pthread_mutex_lock(all->people[ph_nmb - 1].f_mtx);
		*(all->people[ph_nmb - 1].f_frk) = ph_nmb;
		//printf("Philosopher [%d] picked f_fork.\n", ph_nmb);
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
				//printf("Philosopher [%d] dropped f_fork.\n", ph_nmb);
				*(all->people[ph_nmb - 1].f_frk) = -1;
				pthread_mutex_unlock(all->people[ph_nmb - 1].f_mtx);
			}
		}
		else
		{
			//printf("Philosopher [%d] is retrying to eat.\n", ph_nmb);
			*(all->people[ph_nmb - 1].f_frk) = -1;
			pthread_mutex_unlock(all->people[ph_nmb - 1].f_mtx);
			continue ;
		}
		if (all->death_msg == 0)
		{
			pthread_mutex_lock(&all->mtx_msg[0]);
			printf("\033[0;32m%ld %d is eating\033[0m\n", get_time(all), ph_nmb);
			all->people[ph_nmb - 1].last_ate = get_time(all);
			//printf("Philosopher [%d] last ate was: %ld;\n", (ph_nmb - 1), all->people[ph_nmb - 1].last_ate);
			pthread_mutex_unlock(&all->mtx_msg[0]);
		}
		*(all->people[ph_nmb - 1].f_frk) = -1;
		pthread_mutex_unlock(all->people[ph_nmb - 1].f_mtx);
		*(all->people[ph_nmb - 1].p_frk) = -1;
		pthread_mutex_unlock(all->people[ph_nmb - 1].p_mtx);
		break ;
	}
}
/*
//size_t	last_ate;
//	last_ate = all->people[ph_nmb - 1].last_ate;
all->people[ph_nmb - 1].last_ate = get_time(all) - last_ate);

1º forward fork + mutex
2º previous fork + mutex

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
		printf("\033[0;36m%ld %d is sleeping\033[0m\n", get_time(all), ph_nmb);
	pthread_mutex_unlock(&all->mtx_msg[0]);
}
// tirei os while(1) porque eu quero q o programa acabe e nao
// fique ali à espera

void	think_status(t_all *all, int ph_nmb)
{
	pthread_mutex_lock(&all->mtx_msg[0]);
	if (all->death_msg == 0)
		printf("\033[0;34m%ld %d is thinking\033[0m\n", get_time(all), ph_nmb);
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