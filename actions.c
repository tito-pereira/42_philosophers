/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:32:06 by tibarbos          #+#    #+#             */
/*   Updated: 2024/04/23 16:41:45 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating_status(int philo_no)
{
	pthread_mutex_lock(fork_left);
	fork_left = philo_no;
	pthread_mutex_lock(fork_right);
	fork_right = philo_no;
	pthread_mutex_lock(message_board);
	if (fork_left == philo_no && fork_right == philo_no)
		printf("get_timestamp() philo_no eating message");
	pthread_mutex_unlock(message_board);
	pthread_mutex_unlock(fork_left);
	pthread_mutex_unlock(fork_right);
}

void	sleep_status(t_all *all, int ph_nmb)
{
	pthread_mutex_lock(norm_msg);
	while (1)
	{
		if (death_msg == 0)
		{
			printf("%d Philosopher %d is sleeping.\n", get_time(all), ph_nmb);
			break ;
		}
	}
	pthread_mutex_unlock(norm_msg);
}

void	think_status(int ph_nmb)
{
	pthread_mutex_lock(norm_msg);
	while (1)
	{
		if (death_msg == 0)
		{
			printf("%d Philosopher %d is thinking.\n", get_time(), ph_nmb);
			break ;
		}
	}
	pthread_mutex_unlock(norm_msg);
}

void	death_status(int ph_nmb)
{
	pthread_mutex_lock(death_msg);
	printf("%d Philosopher %d has died.\n", get_time(), ph_nmb);
	pthread_mutex_unlock(death_msg);
}