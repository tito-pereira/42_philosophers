/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:19:30 by tibarbos          #+#    #+#             */
/*   Updated: 2024/05/04 20:45:57 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*int	check_hunger(t_all *all, int nbr)
{
	long	hunger;

	hunger = get_time(all) - all->people[nbr - 1].last_ate;
	if (hunger > 0 && (size_t)hunger > all->time_to_die)
	{
		//all->people[nbr - 1].death_time = get_time(all);
		msg_status(all, nbr, 3);
		return (1);
	}
	if (check_global_death(all, 2) == 1)
		return (1);
	return (0);
}*/

int	check_hunger(int mode, t_all *all, int nbr)
{
	long	hunger;
	int		ret;

	ret = 0;
	pthread_mutex_lock(&all->mtx_msg[4]);
	if (mode == 1)
		all->people[nbr - 1].last_ate = get_time(all);
	else if (mode == 2)
	{
		hunger = get_time(all) - all->people[nbr - 1].last_ate;
		if (hunger > 0 && (size_t)hunger > all->time_to_die)
		{
			msg_status(all, nbr, 3);
			ret = 1;
		}
	}
	pthread_mutex_unlock(&all->mtx_msg[4]);
	if (check_global_death(all, 2) == 1 || ret == 1)
		return (1);
	return (0);
}

int	life_cycle(t_all *all, int nbr)
{
	if (eat_status(all, nbr) == 0)
		return (2);
	//if (check_hunger(2, all, nbr) == 1)
		//return (0);
	msg_status(all, nbr, 1);
	usleep(all->time_to_sleep * 1000);
	//if (check_hunger(2, all, nbr) == 1)
		//return (0);
	msg_status(all, nbr, 2);
	usleep(1000);
	return (1);
}

void	*the_philo(void *all_th)
{
	int				i;
	int				lf;
	int				nbr;
	t_all			*all;
	t_all_th		*all_tth;

	i = -1;
	lf = 5;
	all_tth = (t_all_th *)all_th;
	nbr = all_tth->nbr;
	all = all_tth->all;
	while (++i != all->eat_no && check_hunger(2, all, nbr) == 0)
	{
		lf = life_cycle(all, nbr);
		if (lf == 0)
			break ;
		else if (lf == 2)
			continue ;
	}
	return (NULL);
}

void	create_threads(t_all *all, t_all_th **all_th)
{
	int			i;
	pthread_t	reaper_th;

	i = 1;
	while ((i + 1) <= all->philo_num)
	{
		pthread_create(&all->people[i].th, NULL, &the_philo, (void *)all_th[i]);
		i += 2;
	}
	i = 0;
	while ((i + 1) <= all->philo_num)
	{
		pthread_create(&all->people[i].th, NULL, &the_philo, (void *)all_th[i]);
		i += 2;
	}
	pthread_create(&reaper_th, NULL, &the_reaper, (void *)all);
	pthread_join(reaper_th, NULL);
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
