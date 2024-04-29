/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timetables.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:55:49 by marvin            #+#    #+#             */
/*   Updated: 2024/04/26 14:55:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time_s(void)
{
	struct timeval	ct;
	struct timezone	tz;
	size_t			s_curr;

	//printf("Getting current seconds:\n");
	gettimeofday(&ct, &tz);
	s_curr = ct.tv_sec;
	//printf(" %ld;\n", s_curr);
	//printf(" %ld;\n", ct.tv_sec);
	return(s_curr);// * 1000);
}
// returns in seconds

size_t	get_time_us(void)
{
	struct timeval	ct;
	struct timezone	tz;
	size_t			us_curr;

	//printf("Getting current microsseconds:\n");
	gettimeofday(&ct, &tz);
	us_curr = ct.tv_usec;
	//printf(" %ld;\n", us_curr);
	return(us_curr);// / 1000);
}
// return in microsseconds

size_t	get_time(t_all *all)
{
	size_t	us_curr;
	size_t	s_curr;
	size_t	diff_us;
	size_t	sec_passed;
	
	//printf("----------------------\nGetting current time:\n");
	s_curr = get_time_s();
	us_curr = get_time_us();
	sec_passed = s_curr - all->begin_s;
	//printf("s_curr: %ld; us_curr: %ld; sec_pass: %ld;\n", s_curr, us_curr, sec_passed);
	if (us_curr > all->begin_us)
	{
		//printf("curr > begin: diff_us = curr(%ld) - begin(%ld)\n", us_curr, all->begin_us);
		diff_us = us_curr - all->begin_us;
	}
	else
	{
		//printf("begin > curr: diff_us = (1000000 - begin(%ld)) + curr(%ld)\n", all->begin_us, us_curr);
		diff_us = (1000000 - all->begin_us) + us_curr;
		sec_passed--;
	}
	//printf("Result: (%ld * 1000) + (%ld / 1000) = %ld;\n----------------------\n", sec_passed, diff_us, ((sec_passed * 1000) + (diff_us / 1000)));
	return ((sec_passed * 1000) + (diff_us / 1000));
}

/*
seconds: seconds passed since Epoch, January 1970
microsseconds: 0 a 1.000.000

ja nao preciso da thread acho eu (ou preciso?)
basta gravar o segundo inicial, o segundo atual,
fazer a diferenca entre eles e somar *1000 ao resultado
final em milissegundos
*/

/*
size_t	get_time_sub(size_t begin)
{
	struct timeval	ct;
	struct timezone	tz;
	size_t			us_curr;
	size_t			us_old;

	us_old = 0;
	if (begin)
		us_old = begin;
	gettimeofday(&ct, &tz);
	us_curr = ct.tv_usec;
	return((us_curr - us_old) / 1000);
}
*/

/*
size_t	get_time(t_all *all)
{
	size_t	us_curr;
	size_t	s_curr;
	size_t	diff_s;
	size_t	diff_us;
	
	s_curr = get_time_s();
	us_curr = get_time_us();
	if (s_curr > all->times->begin_s)
		diff_s = s_curr - all->times->begin_s;
	else
		diff_s = all->times->begin_s - s_curr;
	diff_s = diff_s * 1000;
	if (us_curr > all->times->begin_s)
		diff_us = us_curr - all->times->begin_us;
	else
		diff_us = all->times->begin_us - us_curr;
    diff_us = diff_us / 1000;
	return ((all->min_passed * 1000) + diff_s + diff_us);
}*/

/*
void	*timetable(void *old_all)
{
	struct timeval	ct;
	struct timezone	tz;
	size_t				sec;
	t_all			*all;
	
	all = (t_all *)old_all;
	while (1)
	{
		gettimeofday(&ct, &tz);
		sec = ct.tv_sec;
		if (sec == 60)
			(all->min_passed)++;
	}
	return(NULL);
}

void	start_time(t_all *all)
{
	pthread_t	th;

	pthread_create(&th, NULL, &timetable, (void *)all);
	all->times->tm_table = &th;
}*/
// is tm_table really necessary anywhere?