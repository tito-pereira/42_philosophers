/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hbx_itoa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 19:06:19 by tibarbos          #+#    #+#             */
/*   Updated: 2023/05/23 17:24:45 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

typedef unsigned int	t_big;

t_big	ft_hbx_set_size(t_big n)
{
	t_big	counter;
	t_big	tmp;

	counter = 1;
	tmp = 1;
	if (n > 0)
	{
		while ((n / tmp) >= 16)
		{
			tmp *= 16;
			counter++;
		}
	}
	return (counter);
}

char	*ft_hbx_reverse(char *str)
{
	t_big	i;
	t_big	size;
	t_big	tmp;

	i = 0;
	size = 0;
	tmp = 0;
	while (str[size] != '\0')
		size++;
	while (i < (size / 2))
	{
		tmp = str[i];
		str[i] = str[size - i - 1];
		str[size - i - 1] = tmp;
		i++;
	}
	return (str);
}

char	*ft_hbx_support(char *ret, t_big tmp, t_big i, t_big n)
{
	t_big	k;
	char	b;

	if (n == 0)
		ret[0] = '0';
	while (tmp > 0)
	{
		k = tmp % 16;
		b = check_letter_bx(k);
		ret[i] = b;
		tmp = tmp / 16;
		i++;
	}
	return (ret);
}

char	*ft_hbx_itoa(unsigned int n)
{
	t_big	i;
	t_big	tmp;
	char	*ret;

	i = 0;
	tmp = n;
	ret = malloc((ft_hbx_set_size(n) + 1) * sizeof(char));
	if (ret == NULL)
		return (NULL);
	ret = ft_hbx_support(ret, tmp, i, n);
	ret[ft_hbx_set_size(n)] = '\0';
	ft_hbx_reverse(ret);
	return (ret);
}
