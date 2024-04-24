/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:47:43 by tibarbos          #+#    #+#             */
/*   Updated: 2024/04/24 12:32:46 by tibarbos         ###   ########.fr       */
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
	int		nbr;
	int		death_status;
	size_t	time_of_death;
	size_t	last_ate;
	int		times_to_eat;
}   t_person;

typedef struct	s_all
{
	int 		philo_num;
	int 		*forks;
	size_t		begin_time;
    size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	int			eat_no;
	int			norm_msg;
	int			death_msg;
	t_person	*people;
}   t_all;
*/

void	starvation(t_person *person, t_all *all)
{
	size_t	hunger;

	hunger = 0;
	while (person->death_status == 0)
	{
		hunger = gettimeofday() - person->last_ate;
		if (hunger > all->time_to_eat)
			person->death_status = 1;
	}
}

void	the_philosopher(t_all *all, int nbr)
{
	t_person	*person;
	pthread_t	t;
	int			i;

	i = -1;
	create_person(nbr, &person);
	all->people[nbr] = person;
	pthread_create(&t, starvation);
	while (++i != all->times_to_eat && person->death_status == 0)
	{
		eating_status(nbr, person->last_ate);
		usleep(all->time_to_eat);
		think_status(nbr);
		sleep_status(nbr);
		usleep(all->time_to_sleep);
	}
	free_person();
}
/*
-> a minha duvida é, se eu abruptamente mudar o death_status para 0,
se causa problemas no loop, memoria etc, ou se o loop espera pela funcao
terminar e quando retorna ao loop simplesmente sai dele

-> pass variables into a thread
-> gettimeofday()
-> usleep()
-> finalizar o mecanismo de life && death_cycles + frees
-> correct thread & mutex syntax
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
*/

int	create_all(char **av, t_all *all)
{
	if (av[0] < 1 || av[1] <= 0 || av[2] <= 0 || av[3] <= 0)
		return(0);
	if (av[4] && av[4] < 0)
		return(0);
	all = malloc(sizeof(t_all));
	all->forks = NULL;
	all->philo_num = av[0];
	all->begin_time = gettimeofday();
	all->time_to_die = av[1];
	all->time_to_eat = av[2];
	all->time_to_sleep = av[3];
	all->eat_no = -1;
	if (av[4])
		all->eat_no = av[4];
	all->norm_msg = 0;
	all->death_msg = 0;
	all->people = malloc(all->philo_num * sizeof(t_person));
	return(1);
}

void	manage_forks(t_all *all, int option)
{
	pthread_mutex_t	forks[all->philo_num];
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
		free_db(all->forks);
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
		all->people = malloc(all->philo_num * sizeof(t_person));
		while (++i < all->philo_num)
		{
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
		manage_people(&all, 1);
		//philos
		manage_forks(&all, 2);
		manage_people(&all, 2);
	}
	else
		printf("Wrong number or invalid arguments.\n");
	return(0);
}