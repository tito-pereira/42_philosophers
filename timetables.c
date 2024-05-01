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

	gettimeofday(&ct, &tz);
	s_curr = ct.tv_sec;
	return(s_curr);
}

size_t	get_time_us(void)
{
	struct timeval	ct;
	struct timezone	tz;
	size_t			us_curr;

	gettimeofday(&ct, &tz);
	us_curr = ct.tv_usec;
	return(us_curr);
}

size_t	get_time(t_all *all)
{
	size_t	us_curr;
	size_t	s_curr;
	size_t	diff_us;
	size_t	sec_passed;
	
	s_curr = get_time_s();
	us_curr = get_time_us();
	sec_passed = s_curr - all->begin_s;
	if (us_curr > all->begin_us)
		diff_us = us_curr - all->begin_us;
	else
	{
		diff_us = (1000000 - all->begin_us) + us_curr;
		sec_passed--;
	}
	return ((sec_passed * 1000) + (diff_us / 1000));
}