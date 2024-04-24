/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:19:30 by tibarbos          #+#    #+#             */
/*   Updated: 2024/04/25 00:02:17 by marvin           ###   ########.fr       */
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
	int				death_msg;
	pthread_mutex_t	*mtx_msg;
	t_person		*people;
}   t_all;
*/

void	*starvation(t_all *all, int n)
{
	unsigned int	hunger;

	hunger = 0;
	while (all->people[n].death_status == 0)
	{
		hunger = get_time(NULL) - all->people[n].last_ate;
		if (hunger > all->time_to_eat)
		{
			all->people[n].death_status = 1;
			all->people[n].time_of_death = get_time(NULL);
		}
	}
}

void	*the_philo(t_all *all, int nbr)
{
	pthread_t	th;
	int			i;
	int			nbr;

	i = -1;
	pthread_create(&th, NULL, &starvation, NULL);
	while (++i != all->eat_no && all->people[nbr].death_status == 0)
	{
		eating_status(all, nbr, all->people[nbr].last_ate);
		usleep(all->time_to_eat * 1000);
		think_status(all, nbr);
		sleep_status(all, nbr);
		usleep(all->time_to_sleep * 1000);
	}
}

void	wake_up_philo(t_all *all)
{
	int	i;

	i = -1;
	while (++i < all->philo_num)
	{
		all->people[i].nbr = i + 1;
		pthread_create(all->people[i].th, NULL, &the_philo, NULL);
	}
	i = -1;
	while (++i < all->philo_num)
		pthread_join(all->people[i].th, NULL);
}
// creates and launches each thread
// and makes the main thread wait for each of them

/*
se o programa tiver que parar assim que um philo morrer, tenho que
retirar as pthread join functions

se calhar posso deixar estar as join functions para garantir
que todas as philo threads dao proper memory free caso seja
necessario
*/