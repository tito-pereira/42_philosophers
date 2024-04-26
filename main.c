/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:47:43 by tibarbos          #+#    #+#             */
/*   Updated: 2024/04/26 15:14:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
Arguments:
- av[0] titulo do programa
- av[1] number_of_philosophers
- av[2] time_to_die
- av[3] time_to_eat
- av[4] time_to_sleep
- av[5] number_of_times_each_philosopher_must_eat (optional)
*/

/*
typedef struct	s_person
{
	pthread_t			th;
	int					nbr;
	int					times_to_eat;
	int					death_status;
	unsigned int		time_of_death;
	unsigned int		last_ate;
}   t_person;

typedef struct	s_all
{
	int 			philo_num;
	size_t			begin_time;
    size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				eat_no;
	int 			*forks;
	pthread_mutex_t	*mtx_frk;
	int				norm_msg;
	int				death_msg;
	pthread_mutex_t	*mtx_msg;
	t_person		*people;
}   t_all;
*/

/*
-> timetables;
-> philo death break;

--- AFTER TESTING ---
-> 1 philosopher behaviour correct?
-> atomic ops ou nao ha nada a fazer;
(caso eu comece a ter stresses com as death messages)
-> bonus e semaphores
(caso eu decida fazer bonus)

pthread_t				<>;
pthread_init			;
pthread_join			;
...
pthread_mutex_t			<name>;
pthread_mutex_init		(<name>, NULL);
pthread_mutex_destroy	(<name>);
...
pthread_mutex_lock		;
pthread_mutex_lock		;
...
usleep()
...
struct timeval current_time;
struct timezone tz;
gettimeofday(&current_time, &tz);

current_time.tv_sec: seconds;
current_time.tv_usec: microsseconds;
*/

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
	(*all)->begin_time = get_time(0);
	printf("begin_time: %zu;\n", (*all)->begin_time); //
	(*all)->time_to_die = ft_atoi(av[2]);
	printf("time_to_die: %zu;\n", (*all)->time_to_die); //
	(*all)->time_to_eat = ft_atoi(av[3]);
	printf("time_to_eat: %zu;\n", (*all)->time_to_eat); //
	(*all)->time_to_sleep = ft_atoi(av[4]);
	printf("time_to_sleep: %zu;\n", (*all)->time_to_sleep); //
	(*all)->eat_no = -2;
	if (av[5])
		(*all)->eat_no = ft_atoi(av[5]);
	printf("eat_no: %d;\n", (*all)->eat_no); //
	(*all)->mtx_frk = NULL;
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
			all->people[i].death_status = 0;
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