/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 11:26:01 by tibarbos          #+#    #+#             */
/*   Updated: 2023/04/28 13:50:16 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	tmp;
	int	sign;

	i = 0;
	sign = 1;
	tmp = 0;
	while (((char *)str)[i] == ' '
		|| (((char *)str)[i] >= 9 && ((char *)str)[i] <= 13))
		i++;
	if (((char *)str)[i] == '-' || ((char *)str)[i] == '+')
	{
		if (((char *)str)[i] == '-')
			sign *= -1;
		i++;
	}
	while (((char *)str)[i] >= '0' && ((char *)str)[i] <= '9')
	{
		tmp = (tmp * 10) + (((char *)str)[i] - 48);
		i++;
	}
	return (sign * tmp);
}

/*int main()
{
    char    str[] = "   -1243abc";

    printf("%d\n", ft_atoi(str));
}*/
