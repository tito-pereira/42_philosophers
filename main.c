/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:47:43 by tibarbos          #+#    #+#             */
/*   Updated: 2024/04/30 11:00:50 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
-> 10ms limit

-> ativar comentarios e ver se algum valor se destaca
-> fazer um esquema geral de todos os valores que uso e criar protecoes extra
+ extra checks c mutex etc. alguma verificacao ta a falhar aqui

4 410 200 200 7
.morrem mesmo no fim, nos 2800
.aparecem 4 mensagens de morte, o que é impensavel

4 410 200 200 8
. exatamente o mesmo nos 3200. tou a fazer algo no fim em q todos morrem

|| morrer no fim ||
philo faz join da starvation. nao da qualquer sinal que completou o numero de vezes
"required" para comer, entao starvation apenas assume que é para continuar a contar, e
eventualmente todos morrem pq starvation em todos acaba
solucao, uma flag no all, c mutex, que notifica sobre "satisfied" ou algo parecido
opa fds p merda daquele free
este é capaz de ser o erro mais irritante que ja alguma vez tive porque faz 0 sentido
porque merda alguma é que funciona c 5 mas nao funciona c 4?

|| multiplas death messages ||
nao deveria acontecer porqueeu ja preveni contra isso. mas testar melhor em casa
(escrevi uma verification check para ver depois)

-- o satisfied status provavelmente tenho que fazer individualmente para cada philo
n faz sentido haver um satsified status global (apesar de se um acabar, todos geralmente
tambem acabam) mas como o codigo vai ser explicado, e mesmo para o CV, é melhor assim
-- como aumentar o numero de testes de modo a que o gajo morra
sera que é contando o tempo na mesma thread que o proprio philo? sera esse o segredo
para atrasar um bcd o tempo? porque contando o tempo à parte nao estou a ver possivelmente
como isto vai crashar, os intervalos de tempo sao no maximo 1ms sao minusculos, nao
chegam àqueles do enunciado 
*/

int	create_all(char **av, t_all **all)
{
	//printf("Creating 'all'.\n"); //
	if (ft_atoi(av[1]) < 1 || ft_atoi(av[2]) <= 0 || ft_atoi(av[3]) <= 0 || ft_atoi(av[4]) <= 0)
		return(0);
	if (av[5] && ft_atoi(av[5]) < 0)
		return(0);
	(*all)->philo_num = ft_atoi(av[1]);
	//printf("philo_num: %d;\n", (*all)->philo_num); //
	(*all)->begin_s = 0;
	(*all)->begin_us = 0;
	(*all)->time_to_die = ft_atoi(av[2]);
	//printf("time_to_die: %ld;\n", (*all)->time_to_die); //
	(*all)->time_to_eat = ft_atoi(av[3]);
	//printf("time_to_eat: %ld;\n", (*all)->time_to_eat); //
	(*all)->time_to_sleep = ft_atoi(av[4]);
	//printf("time_to_sleep: %ld;\n", (*all)->time_to_sleep); //
	(*all)->eat_no = -2;
	if (av[5])
		(*all)->eat_no = ft_atoi(av[5]);
	//printf("eat_no: %d;\n", (*all)->eat_no); //
	(*all)->mtx_frk = NULL;
	(*all)->forks = malloc((*all)->philo_num * sizeof(int));
	(*all)->death_msg = 0;
	(*all)->mtx_msg = NULL;
	(*all)->people = NULL;
	//printf("'all' created.\n");
	return(1);
}

void	manage_forks(t_all *all, int option)
{
	int				i;

	i = -1;
	if (option == 1)
	{
		//printf("Creating fork mutexes:\n"); //
		all->mtx_frk = malloc(all->philo_num * sizeof(pthread_mutex_t));
		while (++i < all->philo_num)
		{
			//printf("init[%d]\n", i); //
			all->forks[i] = -1;
			pthread_mutex_init(&all->mtx_frk[i], NULL);
		}
	}
	else if (option == 2)
	{
		//printf("Destroying fork mutexes:\n"); //
		while (++i < all->philo_num)
		{
			//printf("destroy[%d]\n", i); //
			pthread_mutex_destroy(&all->mtx_frk[i]);
		}
		free(all->mtx_frk);
		free(all->forks);
	}
}
// Option 1: Creates all the forks and their mutexes;
// Option 2: Destroys all the forks and their mutexes;

void	mng_ppl_frk_mtx(t_all *all)
{
	int	i;

	i = -1;
	while (++i < all->philo_num)
	{
		if (i == 0 && all->philo_num == 1)
		{
			//printf("Lone philosopher, fork && mutex NULL.\n");
			all->people[i].p_frk = NULL;
			all->people[i].p_mtx = NULL;
		}
		else if (i == 0 && all->philo_num != 1)
		{
			//printf("Philosopher [%d] previous * == [%d]\n", i, (all->philo_num - 1));
			all->people[i].p_frk = &all->forks[all->philo_num - 1];
			all->people[i].p_mtx = &all->mtx_frk[all->philo_num - 1];
		}
		else
		{
			//printf("Philosopher [%d] previous * == [%d]\n", i, (i - 1));
			all->people[i].p_frk = &all->forks[i - 1];
			all->people[i].p_mtx = &all->mtx_frk[i - 1];
		}
		//printf("Philosopher [%d] forward * == [%d]\n", i, i);
		all->people[i].f_frk = &all->forks[i];
		all->people[i].f_mtx = &all->mtx_frk[i];
	}
}

void	manage_people(t_all *all, int option)
{
	int	i;

	i = -1;
	if (option == 1)
	{
		//printf("Creating people:\n"); //
		all->people = malloc(all->philo_num * sizeof(t_person));
		while (++i < all->philo_num)
		{
			//printf("people[%d]\n", i); //
			all->people[i].th = 0;
			all->people[i].nbr = i + 1;
			all->people[i].stf = 0;
			all->people[i].death_time = 0;
			all->people[i].last_ate = 0;
			all->people[i].times_to_eat = -2;
		}
		mng_ppl_frk_mtx(all);
	}
	else if (option == 2)
	{
		//printf("Destroying people.\n"); //
		free(all->people);
		//printf("People destroyed.\n");
	}
}
/*
nao posso dar free dos pointers aqui porque foram malloc na all struct
e nao na mng_ppl, apenas copia a morada do all->forks e all->frk_mtx
*/
// Option 1: Creates all the t_person structs;
// Option 2: Destroys all the t_person structs;

void	manage_messages(t_all *all, int	option)
{
	if (option == 1)
	{
		//printf("Creating message mutexes.\n"); //
		all->mtx_msg = malloc(3 * sizeof(pthread_mutex_t));
		pthread_mutex_init(&all->mtx_msg[0], NULL);
		pthread_mutex_init(&all->mtx_msg[1], NULL);
		pthread_mutex_init(&all->mtx_msg[2], NULL);
	}
	else if (option == 2)
	{
		//printf("Destroying message mutexes.\n"); //
		pthread_mutex_destroy(&all->mtx_msg[0]);
		pthread_mutex_destroy(&all->mtx_msg[1]);
		pthread_mutex_destroy(&all->mtx_msg[2]);
		free(all->mtx_msg);
	}
}

int	main(int ac, char **av)
{
	t_all	*all;

	if (ac == 5 || (ac == 6 && av[5]))
	{
		//printf("Correct arguments.\n"); //
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
		printf("freeing forks.\n");
		manage_forks(all, 2);
		printf("freeing people.\n");
		manage_people(all, 2);
		printf("freeing msgs.\n");
		manage_messages(all, 2);
		printf("freeing all.\n");
		free(all);
	}
	else
		printf("Wrong number or invalid arguments.\n");
	return(0);
}