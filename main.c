/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:47:43 by tibarbos          #+#    #+#             */
/*   Updated: 2024/04/29 16:42:16 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
-> 10ms limit
-> nao me morre ninguem nos testes que é suposto
*/

int	create_all(char **av, t_all **all)
{
	//printf("Creating 'all'.\n"); //
	if (ft_atoi(av[1]) < 1 || ft_atoi(av[2]) <= 0 || ft_atoi(av[3]) <= 0 || ft_atoi(av[4]) <= 0)
		return(0);
	if (av[5] && ft_atoi(av[5]) < 0)
		return(0);
	//(*all) = malloc(sizeof(t_all));
	(*all)->philo_num = ft_atoi(av[1]);
	//printf("philo_num: %d;\n", (*all)->philo_num); //
	(*all)->begin_s = 0; //get_time_s();
	(*all)->begin_us = 0; //get_time_us();
	(*all)->time_to_die = ft_atoi(av[2]);
	//printf("time_to_die: %ld;\n", (*all)->time_to_die); //
	(*all)->time_to_eat = ft_atoi(av[3]);
	//printf("time_to_eat: %ld;\n", (*all)->time_to_eat); //
	(*all)->time_to_sleep = ft_atoi(av[4]);
	//printf("time_to_sleep: %ld;\n", (*all)->time_to_sleep); //
	(*all)->eat_no = -2;
	if (av[5])
		(*all)->eat_no = ft_atoi(av[5]);
	//printf("eat_no: %d;\n", (*all)->eat_no); //
	(*all)->mtx_frk = NULL;
	(*all)->forks = malloc((*all)->philo_num * sizeof(int));
	(*all)->death_msg = 0;
	(*all)->mtx_msg = NULL;
	(*all)->people = NULL; //malloc((*all)->philo_num * sizeof(t_person));
	//printf("'all' created.\n");
	return(1);
}

void	manage_forks(t_all *all, int option)
{
	int				i;

	i = -1;
	if (option == 1)
	{
		//printf("Creating fork mutexes:\n"); //
		all->mtx_frk = malloc(all->philo_num * sizeof(pthread_mutex_t));
		while (++i < all->philo_num)
		{
			//printf("init[%d]\n", i); //
			all->forks[i] = -1;
			pthread_mutex_init(&all->mtx_frk[i], NULL);
		}
	}
	else if (option == 2)
	{
		//printf("Destroying fork mutexes:\n"); //
		while (++i < all->philo_num)
		{
			//printf("destroy[%d]\n", i); //
			pthread_mutex_destroy(&all->mtx_frk[i]);
		}
		free(all->mtx_frk);
		free(all->forks);
	}
}
// Option 1: Creates all the forks and their mutexes;
// Option 2: Destroys all the forks and their mutexes;

void	mng_ppl_frk_mtx(t_all *all)
{
	int	i;

	i = -1;
	while (++i < all->philo_num)
	{
		if (i == 0 && all->philo_num == 1)
		{
			//printf("Lone philosopher, fork && mutex NULL.\n");
			all->people[i].p_frk = NULL;
			all->people[i].p_mtx = NULL;
		}
		else if (i == 0 && all->philo_num != 1)
		{
			//printf("Philosopher [%d] previous * == [%d]\n", i, (all->philo_num - 1));
			all->people[i].p_frk = &all->forks[all->philo_num - 1];
			all->people[i].p_mtx = &all->mtx_frk[all->philo_num - 1];
		}
		else
		{
			//printf("Philosopher [%d] previous * == [%d]\n", i, (i - 1));
			all->people[i].p_frk = &all->forks[i - 1];
			all->people[i].p_mtx = &all->mtx_frk[i - 1];
		}
		//printf("Philosopher [%d] forward * == [%d]\n", i, i);
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
		//printf("Creating people:\n"); //
		all->people = malloc(all->philo_num * sizeof(t_person));
		while (++i < all->philo_num)
		{
			//printf("people[%d]\n", i); //
			all->people[i].th = 0;
			all->people[i].nbr = i + 1;
			all->people[i].death_time = 0;
			all->people[i].last_ate = 0;
			all->people[i].times_to_eat = -2;
		}
		mng_ppl_frk_mtx(all);
	}
	else if (option == 2)
	{
		//printf("Destroying people.\n"); //
		free(all->people);
		//printf("People destroyed.\n");
	}
}
/*
nao posso dar free dos pointers aqui porque foram malloc na all struct
e nao na mng_ppl, apenas copia a morada do all->forks e all->frk_mtx
*/
// Option 1: Creates all the t_person structs;
// Option 2: Destroys all the t_person structs;

void	manage_messages(t_all *all, int	option)
{
	if (option == 1)
	{
		//printf("Creating message mutexes.\n"); //
		all->mtx_msg = malloc(2 * sizeof(pthread_mutex_t));
		pthread_mutex_init(&all->mtx_msg[0], NULL);
		pthread_mutex_init(&all->mtx_msg[1], NULL);
	}
	else if (option == 2)
	{
		//printf("Destroying message mutexes.\n"); //
		pthread_mutex_destroy(&all->mtx_msg[0]);
		pthread_mutex_destroy(&all->mtx_msg[1]);
		free(all->mtx_msg);
	}
}

int	main(int ac, char **av)
{
	t_all	*all;

	if (ac == 5 || (ac == 6 && av[5]))
	{
		//printf("Correct arguments.\n");
		all = malloc(sizeof(t_all));
		if (create_all(av, &all) == 0)
		{
			printf("Invalid arguments.\n");
			return(0);
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
	return(0);
}

/*while (++i < all->philo_num)
{
	if (all->people[i].p_frk && all->people[i].p_mtx)
	{
		free(all->people[i].p_frk);
		free(all->people[i].p_mtx);
	}
	free(all->people[i].f_frk);
	free(all->people[i].f_mtx);
}*/