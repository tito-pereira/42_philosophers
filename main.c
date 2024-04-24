/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:47:43 by tibarbos          #+#    #+#             */
/*   Updated: 2024/04/24 18:25:24 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
Arguments:
- av[0] number_of_philosophers
- av[1] time_to_die
- av[2] time_to_eat
- av[3] time_to_sleep
- av[4] number_of_times_each_philosopher_must_eat (optional)
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
-> pass variables into a thread (level1 the philo, level 2 starvation)
PRECISO DE PASSAR 2 VARIAVEIS SENAO N VAI FUNCIONAR

-> adjust forks number. only 1 philosopher dies condition on eat_status
should he be stuck trying to eat? should he move on?

-> possible infinite loop conditions waiting for status, especially eating

-> atomic ops ou nao ha nada a fazer;
-> bonus e semaphores

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

int	create_all(char **av, t_all *all)
{
	if (av[0] < 1 || av[1] <= 0 || av[2] <= 0 || av[3] <= 0)
		return(0);
	if (av[4] && av[4] < 0)
		return(0);
	all = malloc(sizeof(t_all));
	all->philo_num = av[0];
	all->begin_time = get_time(NULL);
	all->time_to_die = av[1];
	all->time_to_eat = av[2];
	all->time_to_sleep = av[3];
	all->eat_no = -1;
	if (av[4])
		all->eat_no = av[4];
	all->forks = NULL;
	all->mtx_frk = NULL;
	all->death_msg = 0;
	all->mtx_msg = NULL;
	all->people = malloc(all->philo_num * sizeof(t_person));
	return(1);
}

void	manage_forks(t_all *all, int option)
{
	pthread_mutex_t	*mtxs;
	int				*forks;
	int				i;

	i = -1;
	if (option == 1)
	{
		all->forks = malloc(all->philo_num * sizeof(int *));
		while (++i < all->philo_num)
			pthread_mutex_init(&forks[i], NULL);
	}
	else if (option == 2)
	{
		while (++i < all->philo_num)
			pthread_mutex_destroy(&forks[i]);
		free(all->forks);
		free_db(all->forks);
	}
}
// Option 1: Creates all the forks and their mutexes;
// Option 2: Destroys all the forks and their mutexes;

void	mng_ppl(t_all *all, int option)
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
			all->people[i].death_status = 0;
			all->people[i].time_of_death = 0;
			all->people[i].last_ate = 0;
			all->people[i].times_to_eat = -1;
		}
	}
	else if (option == 2)
		free(all->people);
}
// Option 1: Creates all the t_person structs;
// Option 2: Destroys all the t_person structs;

void	manage_messages(int	option)
{
	pthread_mutex_t	mt[2];
	
	pthread_mutex_init(mt, NULL);
	pthread_mutex_destroy(mt);
}

int	main(int ac, char **av)
{
	t_all	*all;

	if (ac == 5 || (ac == 6 && av[6]))
	{
		all = malloc(sizeof(t_all));
		if (create_all(av, &all) == 0)
		{
			printf("Invalid arguments.\n");
			return(0);
		}
		manage_forks(&all, 1);
		mng_ppl(&all, 1);
		manage_messages(1);
		wake_up_philos(&all);
		mng_forks(&all, 2);
		mng_ppl(&all, 2);
		manage_messages(2);
	}
	else
		printf("Wrong number or invalid arguments.\n");
	return(0);
}