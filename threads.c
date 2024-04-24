/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:19:30 by tibarbos          #+#    #+#             */
/*   Updated: 2024/04/24 16:06:01 by tibarbos         ###   ########.fr       */
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

void	*starvation(t_person *person, t_all *all)
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

void	*the_philo(t_all *all, int nbr)
{
	pthread_t	th;
	int			i;

	i = -1;
	pthread_create(&th, NULL, &starvation, NULL);
	while (++i != all->eat_no && all->people[nbr].death_status == 0)
	{
		eating_status(all, nbr, all->people[nbr].last_ate);
		usleep(all->time_to_eat);
		think_status(all, nbr);
		sleep_status(all, nbr);
		usleep(all->time_to_sleep);
	}
	free_person();
}

/*
os status basicamente abrem e fecham os mutexes das status messages e
printam nas, nada mais nada menos
*/

void	wake_up_philo(t_all *all)
{
	int	i;

	i = -1;
	while (++i < all->philo_num)
		pthread_create(all->people[i].th, NULL, &the_philo, NULL);
	i = -1;
	while (++i < all->philo_num)
		pthread_join(all->people[i].th, NULL);
}
// creates and launches each thread
// and makes the main thread wait for each of them

/*
se o programa tiver que parar assim que um philo morrer, tenho que
retirar as pthread join functions
*/