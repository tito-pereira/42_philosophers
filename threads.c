/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:19:30 by tibarbos          #+#    #+#             */
/*   Updated: 2024/04/25 17:08:38 by tibarbos         ###   ########.fr       */
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

// t_all *all, int n
void	*starvation(void *all_th)
{
	unsigned int	hunger;
	int				nbr;
	t_all			*all;

	hunger = 0;
	nbr = ((t_all_th *)all_th)->nbr;
	printf("Inside philosopher death[%d]\n", nbr);
	all = ((t_all_th *)all_th)->all;
	while (all->people[nbr].death_status == 0)
	{
		printf("Inside philosopher death cycle[%d]\n", nbr);
		hunger = get_time(0) - all->people[nbr].last_ate;
		if (hunger > all->time_to_eat)
		{
			all->people[nbr].death_status = 1;
			all->people[nbr].death_time = get_time(all->people[nbr].last_ate);
		}
	}
	return((void *)all_th);
}
// preciso obrigatoriamente de um return

// t_all *all, int nbr
void	*the_philo(void *all_th)
{
	pthread_t	th;
	int			i;
	int			nbr;
	t_all		*all;

	i = -1;
	nbr = ((t_all_th *)all_th)->nbr;
	printf("Inside philosopher[%d]\n", nbr);
	all = ((t_all_th *)all_th)->all;
	pthread_create(&th, NULL, &starvation, all_th);
	while (++i != all->eat_no && all->people[nbr].death_status == 0)
	{
		printf("Inside philosopher life cycle[%d]\n", nbr);
		eat_status(all, nbr);
		usleep(all->time_to_eat * 1000);
		think_status(all, nbr);
		sleep_status(all, nbr);
		usleep(all->time_to_sleep * 1000);
	}
	free((t_all_th *)all_th);
	return((void *)all_th);
}
// preciso obrigatoriamente de um return

void	wake_up_philos(t_all *all)
{
	int			i;
	t_all_th	**all_th;

	i = -1;
	printf("Waking up philos.\n"); //
	all_th = malloc(all->philo_num * sizeof(t_all_th *));
	while (++i < all->philo_num)
	{
		printf("thread[%d]\n", i); //
		all->people[i].nbr = i + 1;
		all_th[i] = malloc(sizeof(t_all_th));
		all_th[i]->all = all;
		all_th[i]->nbr = i + 1;
		pthread_create(&all->people[i].th, NULL, &the_philo, (void *)all_th);
	}
	i = -1;
	while (++i < all->philo_num)
		pthread_join(all->people[i].th, NULL);
	i = -1;
	while (++i < all->philo_num)
		free(all_th[i]);
	free(all_th);
}
// creates and launches each thread
// and makes the main thread wait for each of them