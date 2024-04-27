/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:19:30 by tibarbos          #+#    #+#             */
/*   Updated: 2024/04/27 17:02:58 by marvin           ###   ########.fr       */
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
	size_t		hunger;
	int		nbr;
	t_all	*all;
	
	hunger = 0;
	nbr = ((t_all_th *)all_th)->nbr;
	printf("Inside philosopher death[%d]\n", nbr);
	all = ((t_all_th *)all_th)->all;
	while (all->death_msg == 0)
	{
		//printf("Inside philosopher death cycle[%d]\n", nbr);
		hunger = get_time(all) - all->people[nbr].last_ate;
		if (hunger > 0 && hunger > all->time_to_die)
		{
			printf("Philosopher [%d] has died\n", nbr);
			printf("hunger %ld: get_time(%ld) - last_ate(%ld)\n", hunger, get_time(all), all->people[nbr].last_ate);
			printf("time_to_die: %ld;\n", all->time_to_die);
			//all->people[nbr].death_status = 1;
			//all->death_msg = 1;
			all->people[nbr].death_time = get_time(all);
			death_status(all, nbr); //msg + death_msg
			break;
		}
	}
	return(NULL);
}
// colocar em unidades / ordens de grandeza comparaveis
// hunger = microsegundos, time_to_eat = milisegundos (micro * 100)
// while (all->people[nbr].death_status == 0)
/* tive que colocar o if hunger > 0 porque, por alguma razao, os primeiros
loops ainda me apareciam um get_time = 0 e dava resultados negativos
e passava o limite inferior de size_t para valores absurdos e entao
hunger era sempre maior que time_to_die (quando na realidade eram
apenas valores negativos)
o que por si só nunca deveria acontecer porque get_time nunca
deveria ser inferior ao begin_time, nao faz sentido
*/

// t_all *all, int nbr
void	*the_philo(void *all_th)
{
	pthread_t	th;
	int				i;
	int				nbr;
	t_all			*all;
	t_all_th		*all_tth;

	i = -1;
	all_tth = (t_all_th *)all_th; 
	nbr = all_tth->nbr;
	//printf("Inside philosopher[%d]\n", nbr);
	all = all_tth->all;
	//printf("Creating death in philosopher[%d]\n", nbr);
	pthread_create(&th, NULL, &starvation, all_th);
	while (++i != all->eat_no && all->death_msg == 0)
	{
		//printf("Inside philosopher life cycle[%d]\n", nbr);
		eat_status(all, nbr);
		usleep(all->time_to_eat * 1000);
		think_status(all, nbr);
		sleep_status(all, nbr);
		usleep(all->time_to_sleep * 1000);
	}
	return(NULL);
}
// preciso obrigatoriamente de um return por ser (void *)
// while (++i != all->eat_no && all->people[nbr].death_status == 0)

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
		printf("created nbr is %d.\n", all_th[i]->nbr);
		pthread_create(&all->people[i].th, NULL, &the_philo, (void *)all_th[i]);
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

/*
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