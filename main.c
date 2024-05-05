/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:47:43 by tibarbos          #+#    #+#             */
/*   Updated: 2024/05/05 17:41:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	manage_forks(t_all *all, int option)
{
	int		i;

	i = -1;
	if (option == 1)
	{
		all->mtx_frk = malloc(all->philo_num * sizeof(pthread_mutex_t));
		while (++i < all->philo_num)
		{
			all->forks[i] = -1;
			pthread_mutex_init(&all->mtx_frk[i], NULL);
		}
	}
	else if (option == 2)
	{
		while (++i < all->philo_num)
			pthread_mutex_destroy(&all->mtx_frk[i]);
		free(all->mtx_frk);
		free(all->forks);
	}
}

void	mng_ppl_frk_mtx(t_all *all)
{
	int	i;

	i = -1;
	while (++i < all->philo_num)
	{
		if (i == 0 && all->philo_num == 1)
		{
			all->people[i].p_frk = NULL;
			all->people[i].p_mtx = NULL;
		}
		else if (i == 0 && all->philo_num != 1)
		{
			all->people[i].p_frk = &all->forks[all->philo_num - 1];
			all->people[i].p_mtx = &all->mtx_frk[all->philo_num - 1];
		}
		else
		{
			all->people[i].p_frk = &all->forks[i - 1];
			all->people[i].p_mtx = &all->mtx_frk[i - 1];
		}
		all->people[i].f_frk = &all->forks[i];
		all->people[i].f_mtx = &all->mtx_frk[i];
	}
}

void	manage_people(t_all *all, int option)
{
	int	i;

	i = -1;
	if (option == 1)
	{
		all->people = malloc(all->philo_num * sizeof(t_person));
		while (++i < all->philo_num)
		{
			all->people[i].th = 0;
			all->people[i].nbr = i + 1;
			all->people[i].last_ate = 0;
			all->people[i].times_ate = 0;
		}
		mng_ppl_frk_mtx(all);
	}
	else if (option == 2)
		free(all->people);
}

void	manage_messages(t_all *all, int option)
{
	if (option == 1)
	{
		all->mtx_msg = malloc(5 * sizeof(pthread_mutex_t));
		pthread_mutex_init(&all->mtx_msg[0], NULL);
		pthread_mutex_init(&all->mtx_msg[1], NULL);
		pthread_mutex_init(&all->mtx_msg[2], NULL);
		pthread_mutex_init(&all->mtx_msg[3], NULL);
		pthread_mutex_init(&all->mtx_msg[4], NULL);
	}
	else if (option == 2)
	{
		pthread_mutex_destroy(&all->mtx_msg[0]);
		pthread_mutex_destroy(&all->mtx_msg[1]);
		pthread_mutex_destroy(&all->mtx_msg[2]);
		pthread_mutex_destroy(&all->mtx_msg[3]);
		pthread_mutex_destroy(&all->mtx_msg[4]);
		free(all->mtx_msg);
	}
}

int	main(int ac, char **av)
{
	t_all	*all;

	if (ac == 5 || (ac == 6 && av[5]))
	{
		all = malloc(sizeof(t_all));
		if (create_all(av, &all) == 0)
		{
			free(all);
			printf("Invalid arguments.\n");
			return (0);
		}
		manage_forks(all, 1);
		manage_people(all, 1);
		manage_messages(all, 1);
		wake_up_philos(all);
		manage_forks(all, 2);
		manage_people(all, 2);
		manage_messages(all, 2);
		free(all);
	}
	else
		printf("Wrong number or invalid arguments.\n");
	return (0);
}
