/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:47:43 by tibarbos          #+#    #+#             */
/*   Updated: 2024/04/23 17:30:20 by tibarbos         ###   ########.fr       */
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

void	starvation()
{
	while (person->death_status == 0)
	{
		hunger = gettimeofday() - person->last_ate
		death_status = 1;
	}
}

void	the_philo(t_all *all, int nbr)
{
	t_person	*person;
	pthread_t	t;
	int			i;

	i = 0;
	create_person(nbr, &person);
	all->people[nbr] = person;
	pthread_create(&t, starvation);
	while (i != all->times_to_eat && person->death_status == 0)
	{
		eating_status(nbr, person->last_ate);
		usleep(all->time_to_eat);
		think_status(nbr);
		sleep_status(nbr);
		usleep(all->time_to_sleep);
	}
}

/*
por default, inicializar o times to eat para -1
assim, caso nao haja a opcao, essa condicao vai ser sempre falsa e,
caso haja opcao, eventualmente vai ser verdadeira
*/

/*
typedef struct	s_all
{
	int philo_num;
	int *forks;
	size_t	begin_time;
    size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	int		eat_no;
	int		norm_msg;
	int		death_msg;
}   t_all;
*/

int	create_all(char **av, t_all *all)
{
	if (av[0] < 1 || av[1] <= 0 || av[2] <= 0 || av[3] <= 0)
		return(0);
	if (av[4] && av[4] < 0)
		return(0);
	all = malloc(sizeof(t_all));
	all->philo_num = av[0];
	all->begin_time = gettimeofday();
	all->time_to_die = av[1];
	all->time_to_eat = av[2];
	all->time_to_sleep = av[3];
	all->eat_no = -1;
	if (av[4])
		all->eat_no = av[4];
	all->norm_msg;
	all->death_msg;
	all->people = malloc(all->philo_num * sizeof(t_person));
	return(1);
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
	}
	else
		printf("Wrong number or invalid arguments.\n");
}