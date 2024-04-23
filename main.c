/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:47:43 by tibarbos          #+#    #+#             */
/*   Updated: 2024/04/23 13:24:57 by tibarbos         ###   ########.fr       */
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

// cada thread individual
void	the_philo(t_all *all)
{
	// stuff;
	while (i != times_to_eat)
	{
		ez;
	}
}
/*
por default, inicializar o times to eat para -1
assim, caso nao haja a opcao, essa condicao vai ser sempre falsa e,
caso haja opcao, eventualmente vai ser verdadeira
*/

int	main(int ac, char **av)
{
	t_all	*all;

	if (ac == 5 || (ac == 6 && av[6]))
	{
		all = malloc(sizeof(t_all));
		create_all(av, &all);
		all->begin_time = gettimeofday();
		all->eat_no = -1;
		if (av[4])
			all.eat_no = av[4];
	}
	else
		printf("Wrong number or invalid arguments.\n");
}