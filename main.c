/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:47:43 by tibarbos          #+#    #+#             */
/*   Updated: 2024/04/27 17:57:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
-> fork concurrency problem
cada 1 pega num fork e fica so c um e morrem todos

-> timestamps ()
-> philo death break program ()
-> smaller usleep() timers
-> different prinft colors
-> 10ms limit

--- AFTER TESTING ---
-> 1 philosopher behaviour correct?
-> atomic ops ou nao ha nada a fazer;
(caso eu comece a ter stresses com as death messages)
-> bonus e semaphores
(caso eu decida fazer bonus)
*/

/*
void	init_time(t_all *all)
{
	printf("Initiating time info.\n");
	all->min_passed = 0;
	printf("min_passed: %d;\n", all->min_passed);
	all->times->begin_s = get_time_s();
	printf("begin_s: %ld;\n", all->times->begin_s);
	if (all->times->begin_s == 60)
		(all->min_passed)++;
	all->times->begin_us = get_time_us();
	printf("begin_us: %ld;\n", all->times->begin_us);
	printf("min_passed: %d;\n", all->min_passed);
}*/

int	create_all(char **av, t_all **all)
{
	printf("Creating 'all'.\n"); //
	if (ft_atoi(av[1]) < 1 || ft_atoi(av[2]) <= 0 || ft_atoi(av[3]) <= 0 || ft_atoi(av[4]) <= 0)
		return(0);
	if (av[5] && ft_atoi(av[5]) < 0)
		return(0);
	(*all) = malloc(sizeof(t_all));
	(*all)->philo_num = ft_atoi(av[1]);
	printf("philo_num: %d;\n", (*all)->philo_num); //
	(*all)->begin_s = get_time_s();
	(*all)->begin_us = get_time_us();
	(*all)->time_to_die = ft_atoi(av[2]);
	printf("time_to_die: %ld;\n", (*all)->time_to_die); //
	(*all)->time_to_eat = ft_atoi(av[3]);
	printf("time_to_eat: %ld;\n", (*all)->time_to_eat); //
	(*all)->time_to_sleep = ft_atoi(av[4]);
	printf("time_to_sleep: %ld;\n", (*all)->time_to_sleep); //
	(*all)->eat_no = -2;
	if (av[5])
		(*all)->eat_no = ft_atoi(av[5]);
	printf("eat_no: %d;\n", (*all)->eat_no); //
	(*all)->mtx_frk = NULL;
	//(*all)->forks = malloc((*all)->philo_num * sizeof(int));
	//memset(forks, -1, (*all)->philo_num);
	(*all)->death_msg = 0;
	(*all)->mtx_msg = NULL;
	(*all)->people = malloc((*all)->philo_num * sizeof(t_person));
	printf("'all' created.\n");
	return(1);
}

void	manage_forks(t_all *all, int option)
{
	int				i;

	i = -1;
	if (option == 1)
	{
		printf("Creating fork mutexes:\n"); //
		all->mtx_frk = malloc(all->philo_num * sizeof(pthread_mutex_t));
		while (++i < all->philo_num)
		{
			printf("init[%d]\n", i); //
			pthread_mutex_init(&all->mtx_frk[i], NULL);
		}
	}
	else if (option == 2)
	{
		printf("Destroying fork mutexes:\n"); //
		while (++i < all->philo_num)
		{
			printf("destroy[%d]\n", i); //
			pthread_mutex_destroy(&all->mtx_frk[i]);
		}
		free(all->mtx_frk);
	}
}
// Option 1: Creates all the forks and their mutexes;
// Option 2: Destroys all the forks and their mutexes;

void	manage_people(t_all *all, int option)
{
	int	i;

	i = -1;
	if (option == 1)
	{
		printf("Creating people:\n"); //
		all->people = malloc(all->philo_num * sizeof(t_person));
		while (++i < all->philo_num)
		{
			printf("people[%d]\n", i); //
			all->people[i].th = 0;
			all->people[i].nbr = i + 1;
			//all->people[i].death_status = 0;
			all->people[i].death_time = 0;
			all->people[i].last_ate = 0;
			all->people[i].times_to_eat = -2;
		}
	}
	else if (option == 2)
	{
		printf("Destroying people.\n"); //
		free(all->people);
	}
}
// Option 1: Creates all the t_person structs;
// Option 2: Destroys all the t_person structs;

void	manage_messages(t_all *all, int	option)
{
	if (option == 1)
	{
		printf("Creating message mutexes.\n"); //
		all->mtx_msg = malloc(2 * sizeof(pthread_mutex_t));
		pthread_mutex_init(&all->mtx_msg[0], NULL);
		pthread_mutex_init(&all->mtx_msg[1], NULL);
	}
	else if (option == 2)
	{
		printf("Destroying message mutexes.\n"); //
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
		printf("Correct arguments.\n");
		all = malloc(sizeof(t_all));
		if (create_all(av, &all) == 0)
		{
			printf("Invalid arguments.\n");
			return(0);
		}
		//start_time(all);
		manage_forks(all, 1);
		manage_people(all, 1);
		manage_messages(all, 1);
		wake_up_philos(all);
		manage_forks(all, 2);
		manage_people(all, 2);
		manage_messages(all, 2);
	}
	else
		printf("Wrong number or invalid arguments.\n");
	return(0);
}

/*
se for preciso poupar linhas, colocar os manage(1) dentro
do create_all e so deixar os (2) ca fora

. get_time(1000) imediato nem da tempo de comer;
. fica dentro do loop de morte a imprimir ate a thread finalmente atualizar

current testing

global death status
- eliminei o death status individual em cada people[]
- coloquei um death_msg global no all

time
- t_all struct -> times*
- create_all (init_time);
- start_time(main);
- get_time_tt(); actions / threads
*/