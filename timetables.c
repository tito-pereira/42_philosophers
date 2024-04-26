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

int	get_time_s(void)
{
	struct timeval	ct;
	struct timezone	tz;
	size_t			s_curr;

	gettimeofday(&ct, &tz);
	s_curr = ct.tv_sec;
	return(s_curr * 1000);
}

int	get_time_us(void)
{
	struct timeval	ct;
	struct timezone	tz;
	size_t			us_curr;

	gettimeofday(&ct, &tz);
	us_curr = ct.tv_usec;
	return(us_curr / 1000);
}

int	get_c_time(t_all *all)
{
	int	us_curr;
	int	s_curr;
	
	s_curr = get_time_s(void);
	us_curr = get_time_us(void);
	if (s_curr > all->begin_s)
		diff_s = s_curr - all->begin_s;
	else
		diff_s = all->begin_s - s_curr;
	diff_s = diff_s * 1000;
	if (us_curr > all->begin_s)
		diff_us = us_curr - all->begin_us;
	else
		diff_us = all->begin_us - us_curr;
    diff_us = diff_us / 1000;
	return ((all->min_passed * 1000) + diff_s + diff_us);
}

void	*timetable(void *all)
{
	struct timeval	ct;
	struct timezone	tz;
	int				sec;
	
	while (1)
	{
		gettimeofday(&ct, &tz);
		sec = ct.tv_sec;
		if (sec == 60)
			(all->min_passed)++;
	}
	return(NULL);
}