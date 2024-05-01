/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:19:30 by tibarbos          #+#    #+#             */
/*   Updated: 2024/05/01 18:09:31 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*starvation(void *all_th)
{
	long		hunger;
	int			nbr;
	t_all		*all;
	t_all_th	*all_tth;
	
	hunger = 0;
	all_tth = (t_all_th *)all_th; 
	nbr = all_tth->nbr;
	all = all_tth->all;
	while (all->death_msg == 0 && all->people[nbr - 1].stf == 0)
	{
		hunger = get_time(all) - all->people[nbr - 1].last_ate;
		if (hunger > 0 && (size_t)hunger > all->time_to_die)
		{
			all->people[nbr - 1].death_time = get_time(all);
			death_status(all, nbr);
			break;
		}
	}
	return(NULL);
}

void	*the_philo(void *all_th)
{
	pthread_t		th;
	int				i;
	int				nbr;
	t_all			*all;
	t_all_th		*all_tth;

	i = -1;
	all_tth = (t_all_th *)all_th; 
	nbr = all_tth->nbr;
	all = all_tth->all;
	pthread_create(&th, NULL, &starvation, all_th);
	//usleep((nbr) * DELAY);
	while (++i != all->eat_no && all->death_msg == 0)
	{
		eat_status(all, nbr);
		sleep_status(all, nbr);
		usleep(all->time_to_sleep * 1000);
		think_status(all, nbr);
		usleep(1000);
	}
	if (i == all->eat_no)
		all->people[nbr - 1].stf = 1;
	pthread_join(th, NULL);
	return(NULL);
}

void	wake_up_philos(t_all *all)
{
	int			i;
	t_all_th	**all_th;

	i = -1;
	all->begin_s = get_time_s();
	all->begin_us = get_time_us();
	all_th = (t_all_th **)malloc(all->philo_num * sizeof(t_all_th *));
	while (++i < all->philo_num)
	{
		all->people[i].nbr = i + 1;
		all_th[i] = malloc(sizeof(t_all_th));
		all_th[i]->all = all;
		all_th[i]->nbr = i + 1;
		pthread_create(&all->people[i].th, NULL, &the_philo, (void *)all_th[i]);
	}
	i = -1;
	while (++i < all->philo_num)
		pthread_join(all->people[i].th, NULL);
	i = -1;
	while (++i < all->philo_num)
		free(all_th[i]);
	free(all_th);
}