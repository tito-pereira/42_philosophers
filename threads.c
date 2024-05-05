/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:19:30 by tibarbos          #+#    #+#             */
/*   Updated: 2024/05/05 17:40:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	life_cycle(t_all *all, int nbr)
{
	if (eat_status(all, nbr) == 0)
		return (2);
	msg_status(all, nbr, 1);
	usleep(all->time_to_sleep * 1000);
	msg_status(all, nbr, 2);
	usleep(1000);
	return (1);
}

void	green_light(t_all *all)
{
	while (1)
	{
		if (start_race(2, all) == 0)
			continue ;
		else
			break ;
	}
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
	green_light(all);
	if ((nbr % 2) != 0 && all->philo_num != 1)
		usleep((all->time_to_eat / 2) * 1000);
	while (++i != all->eat_no && check_hunger(2, all, nbr) == 0)
	{
		lf = life_cycle(all, nbr);
		if (lf == 2)
		{
			i = -1;
			continue ;
		}
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
		start_race(1, all);
	}
	i = 0;
	while ((i + 1) <= all->philo_num)
	{
		pthread_create(&all->people[i].th, NULL, &the_philo, (void *)all_th[i]);
		i += 2;
		start_race(1, all);
	}
	start_race(3, all);
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
	create_threads(all, all_th);
	i = -1;
	while (++i < all->philo_num)
		pthread_join(all->people[i].th, NULL);
	i = -1;
	while (++i < all->philo_num)
		free(all_th[i]);
	free(all_th);
}
