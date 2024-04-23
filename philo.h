/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:48:12 by tibarbos          #+#    #+#             */
/*   Updated: 2024/04/23 13:24:07 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>

/*
typedef struct	s_times() {
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
}   t_times;*/

typedef struct	s_all
{
	int philo_num;
	int *forks;
	//t_times *times;
	size_t	begin_time;
    size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
}   t_all;

#endif