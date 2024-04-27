/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:48:12 by tibarbos          #+#    #+#             */
/*   Updated: 2024/04/27 17:56:10 by marvin           ###   ########.fr       */
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
	pthread_t	th;
	int			nbr;
	int			times_to_eat;
	//int			death_status;
	size_t			death_time;
	size_t			last_ate;
}   t_person;

typedef struct	s_times
{
	size_t				begin_s;
	size_t				begin_us;
	int				min_passed;
	pthread_t	*tm_table;
}   t_times;
// is tm_table really necessary anywhere?

typedef struct	s_all
{
	int 			philo_num;
	size_t			begin_s;
	size_t			begin_us;
    size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				min_passed;
	int				eat_no;
	pthread_mutex_t	*mtx_frk;
	int				death_msg;
	pthread_mutex_t	*mtx_msg;
	t_person		*people;
}   t_all;
// int	*forks;

typedef	struct s_all_sh
{
	t_all	*all;
	int		nbr;
}	t_all_th;


// ACTIONS
size_t	get_time_sub(size_t begin);
void	eat_status(t_all *all, int ph_nmb);
void	sleep_status(t_all *all, int ph_nmb);
void	think_status(t_all *all, int ph_nmb);
void	death_status(t_all *all, int ph_nmb);

// THREADS
void	wake_up_philos(t_all *all);

// EXTRA
int		ft_atoi(char *str);

// TIMETABLES
size_t		get_time_s(void);
size_t		get_time_us(void);
size_t		get_time(t_all *all);
void	*timetable(void *old_all);
void	start_time(t_all *all);

#endif