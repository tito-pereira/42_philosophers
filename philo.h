/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:48:12 by tibarbos          #+#    #+#             */
/*   Updated: 2024/05/02 18:23:02 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct	s_person
{
	pthread_t		th;
	int				nbr;
	int				times_to_eat;
	int				stf;
	size_t			death_time;
	size_t			last_ate;
	int				*p_frk;
	int				*f_frk;
	pthread_mutex_t	*p_mtx;
	pthread_mutex_t	*f_mtx;
}   t_person;

typedef struct	s_all
{
	int 			philo_num;
	size_t			begin_s;
	size_t			begin_us;
    size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				eat_no;
	int				global;
	pthread_mutex_t	*mtx_frk;
	int				*forks;
	int				death_msg;
	pthread_mutex_t	*mtx_msg;
	t_person		*people;
}   t_all;

typedef	struct s_all_sh
{
	t_all	*all;
	int		nbr;
}	t_all_th;


// ACTIONS
int		eat_status(t_all *all, int ph_nmb);
void	msg_status(t_all *all, int ph_nmb, int opt);

// THREADS
void	wake_up_philos(t_all *all);
int		check_hunger(t_all *all, int nbr);
int		check_global_death(t_all *all, int source);

// EXTRA
int		ft_atoi(char *str);
int		create_all(char **av, t_all **all);

// TIMETABLES
size_t	get_time_s(void);
size_t	get_time_us(void);
size_t	get_time(t_all *all);

#endif