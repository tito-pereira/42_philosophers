/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:19:30 by tibarbos          #+#    #+#             */
/*   Updated: 2024/04/30 11:02:31 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*starvation(void *all_th)
{
	long		hunger;
	int			nbr;
	t_all		*all;
	t_all_th	*all_tth;
	
	hunger = 0;
	all_tth = (t_all_th *)all_th; 
	nbr = all_tth->nbr;
	all = all_tth->all;
	//printf("Inside philosopher death[%d]\n", (nbr - 1)); //
	while (all->death_msg == 0 && all->people[nbr - 1].stf == 0)
	{
		//printf("Inside philosopher death cycle[%d]\n", nbr); //
		hunger = get_time(all) - all->people[nbr - 1].last_ate;
		if (hunger > 0 && (size_t)hunger > all->time_to_die)
		{
			//printf("Philosopher [%d] has died\n", nbr); //
			//printf("(starve)hunger %zu: get_time(%zu) - last_ate(%zu)\n", hunger, get_time(all), all->people[nbr - 1].last_ate); //
			//printf("time_to_die: %zu;\n", all->time_to_die); //
			all->people[nbr - 1].death_time = get_time(all);
			death_status(all, nbr);
			break;
		}
	}
	//printf("Philosopher [%d] will be buried.\n", (nbr - 1)); //
	return(NULL);
}
// hunger = microsegundos, time_to_eat = milisegundos (micro * 100)
// while (all->people[nbr].death_status == 0)

void	*the_philo(void *all_th)
{
	pthread_t		th;
	int				i;
	int				nbr;
	t_all			*all;
	t_all_th		*all_tth;

	i = -1;
	all_tth = (t_all_th *)all_th; 
	nbr = all_tth->nbr;
	all = all_tth->all;
	pthread_create(&th, NULL, &starvation, all_th);
	usleep((nbr) * DELAY);
	//printf("Inside philosopher[%d]\n", (nbr - 1)); //2
	while (++i != all->eat_no && all->death_msg == 0)
	{
		//printf("Inside philosopher life cycle[%d]\n", nbr); //
		printf("Philosopher [%d] hunger before eating:\n", (nbr - 1)); //
		printf("hunger %zu: get_time(%zu) - last_ate(%zu)\n", (get_time(all) - all->people[nbr - 1].last_ate), get_time(all), all->people[nbr - 1].last_ate); //
		eat_status(all, nbr);
		usleep(all->time_to_eat * 1000);
		printf("Philosopher [%d] hunger before thinking:\n", (nbr - 1)); //
		printf("hunger %zu: get_time(%zu) - last_ate(%zu)\n", (get_time(all) - all->people[nbr - 1].last_ate), get_time(all), all->people[nbr - 1].last_ate); //
		think_status(all, nbr);
		printf("Philosopher [%d] hunger before sleeping:\n", (nbr - 1)); //
		printf("hunger %zu: get_time(%zu) - last_ate(%zu)\n", (get_time(all) - all->people[nbr - 1].last_ate), get_time(all), all->people[nbr - 1].last_ate); //
		sleep_status(all, nbr);
		usleep(all->time_to_sleep * 1000);
	}
	if (i == all->eat_no)
		all->people[nbr - 1].stf == 1;
	pthread_join(th, NULL);
	//printf("Philosopher [%d] is abandoning.\n", (nbr - 1)); //
	return(NULL);
}

void	wake_up_philos(t_all *all)
{
	int			i;
	t_all_th	**all_th;//[all->philo_num];

	i = -1;
	//printf("Waking up philos.\n"); //
	all->begin_s = get_time_s();
	all->begin_us = get_time_us();
	//printf("Begin time: %zu;\n", get_time(all)); //
	all_th = (t_all_th **)malloc(all->philo_num * sizeof(t_all_th *));
	while (++i < all->philo_num)
	{
		//printf("thread[%d]\n", i); //
		all->people[i].nbr = i + 1;
		all_th[i] = malloc(sizeof(t_all_th));
		all_th[i]->all = all;
		all_th[i]->nbr = i + 1;
		//printf("created nbr is %d.\n", all_th[i]->nbr); //
		pthread_create(&all->people[i].th, NULL, &the_philo, (void *)all_th[i]);
	}
	i = -1;
	while (++i < all->philo_num)
		pthread_join(all->people[i].th, NULL);
	i = -1;
	//printf("lets find that invalid shit.\n");
	while (++i < all->philo_num)
	{
		//printf("is is individual [%d] pointer?\n", i);
		free(all_th[i]);
	}
	printf("is it the main ** pointer?\n");
	free(all_th);
	printf("all good now?\n");
}
// creates and launches each thread
// and makes the main thread wait for each of them

/*
comecar a contagem de tempo so aqui diria eu;

old tests
if (i && all->eat_no && all->people[nbr].death_status)
		printf("i:%d, eat_no:%d, death_status: %d. Why not looping?\n", i, all->eat_no, all->people[nbr].death_status);
	if (i)
		printf("i exists: %d;\n", i);
	else
		printf("i is NULL\n");
	if (all->eat_no)
		printf("eat_no exists: %d;\n", all->eat_no);
	else
		printf("eat_no is NULL\n");
	if (all->people[nbr].death_status)
		printf("death_status exists: %d;\n", all->people[nbr].death_status);
	else
		printf("death_status is NULL\n");

void	print_people(t_all *all)
{
	int i = -1;
	while (++i < all->philo_num) {
		printf("people[%d] nbr: %d\n", i, all->people[i].nbr);
		printf("people[%d] times_to_eat %d\n", i, all->people[i].times_to_eat);
		printf("people[%d] death_status %d\n", i, all->people[i].death_status);
		printf("people[%d] death_time %zu\n", i, all->people[i].death_time);
		printf("people[%d] last_ate %zu\n", i, all->people[i].last_ate);
	}
}

void	print_all(t_all *all)
{
	printf("philo_num %d;\n", all->philo_num);
	printf("begin_time %zu;\n", all->begin_time);
	printf("time_to_die %zu;\n", all->time_to_die);
	printf("time_to_eat %zu;\n", all->time_to_eat);
	printf("time_to_sleep %zu;\n", all->time_to_sleep);
	printf("eat_no %d;\n", all->eat_no);
	printf("death_msg %d;\n", all->death_msg);
	if (all->mtx_frk)
		printf("mtx_frk exists.\n");
	if (all->mtx_msg)
		printf("mtx_msg exists.\n");
	print_people(all);
}
*/