/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:19:30 by tibarbos          #+#    #+#             */
/*   Updated: 2024/05/02 14:02:06 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	see_hunger(t_all *all)
{
	long	hunger;
	int		nbr;

	if (all->death_msg == 1)
		return(1);
	//printf("all->death_msg was %d\n", all->death_msg);
	nbr = all->philo_num;
	//printf("philo nbr is %d\n", nbr);
	hunger = get_time(all) - all->people[nbr - 1].last_ate;
	//printf("hunger: %zu, time to die: %zu;\n", hunger, all->time_to_die);
	if (hunger > 0 && (size_t)hunger > all->time_to_die)
	{
		//printf("return 1\n");
		return(1);
	}
	//printf("return 0\n");
	return(0);
}

int	check_hunger(t_all *all)
{
	long	hunger;
	int		nbr;

	if (all->death_msg == 1)
		return(1);
	nbr = all->philo_num;
	hunger = get_time(all) - all->people[nbr - 1].last_ate;
	//printf("hunger: %ld, time to die: %zu;\n", hunger, all->time_to_die); //
	if (hunger > 0 && (size_t)hunger > all->time_to_die)
	{
		all->people[nbr - 1].death_time = get_time(all);
		msg_status(all, nbr, 3);
		return(1);
	}
	return(0);
}

void	*the_philo(void *all_th)
{
	int				i;
	int				nbr;
	t_all			*all;
	t_all_th		*all_tth;

	i = -1;
	all_tth = (t_all_th *)all_th; 
	nbr = all_tth->nbr;
	all = all_tth->all;
	while (++i != all->eat_no && check_hunger(all) == 0)
	{
		if (eat_status(all, nbr) == 0)
			continue;
		msg_status(all, nbr, 1);
		usleep(all->time_to_sleep * 1000);
		msg_status(all, nbr, 2);
		usleep(1000);
	}
	if (i == all->eat_no)
		all->people[nbr - 1].stf = 1;
	return(NULL);
}

void	create_threads(t_all *all, t_all_th **all_th)
{
	int	i;
	
	i = 0;
	while ((i + 1) <= all->philo_num) {
		pthread_create(&all->people[i].th, NULL, &the_philo, (void *)all_th[i]);
		i += 2;
	}
	i = 1;
	while ((i + 1) <= all->philo_num) {
		pthread_create(&all->people[i].th, NULL, &the_philo, (void *)all_th[i]);
		i += 2;
	}
}

void	wake_up_philos(t_all *all)
{
	int			i;
	t_all_th	**all_th;

	i = -1;
	all_th = (t_all_th **)malloc(all->philo_num * sizeof(t_all_th *));
	while (++i < all->philo_num)
	{
		all->people[i].nbr = i + 1;
		all_th[i] = malloc(sizeof(t_all_th));
		all_th[i]->all = all;
		all_th[i]->nbr = i + 1;
	}
	all->begin_s = get_time_s();
	all->begin_us = get_time_us();
	create_threads(all, all_th);
	i = -1;
	while (++i < all->philo_num)
		pthread_join(all->people[i].th, NULL);
	i = -1;
	while (++i < all->philo_num)
		free(all_th[i]);
	free(all_th);
}