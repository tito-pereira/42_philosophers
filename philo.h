/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:48:12 by tibarbos          #+#    #+#             */
/*   Updated: 2024/04/24 11:05:11 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>

typedef struct	s_person
{
	int		nbr;
	int		death_status;
	size_t	time_of_death;
	size_t	last_ate;
	int		times_to_eat;
}   t_person;

typedef struct	s_all
{
	int 		philo_num;
	int 		*forks;
	size_t		begin_time;
    size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	int			eat_no;
	int			norm_msg;
	int			death_msg;
	t_person	*people;
}   t_all;

#endif