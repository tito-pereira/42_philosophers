/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 19:46:14 by tibarbos          #+#    #+#             */
/*   Updated: 2023/05/23 17:35:13 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_set_size(int n)
{
	int	counter;
	int	tmp;

	counter = 1;
	tmp = 1;
	if (n < 0)
		n *= -1;
	if (n > 0)
	{
		while ((n / tmp) >= 10)
		{
			tmp *= 10;
			counter++;
		}
	}
	if (n == -2147483648)
		counter = 10;
	return (counter);
}

char	*ft_reverse(char *str)
{
	int	i;
	int	size;
	int	tmp;

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

char	*ft_support(char *ret, unsigned int tmp, int i, int n)
{
	if (n < 0)
		tmp *= -1;
	if (n == 0)
		ret[0] = '0';
	while (tmp > 0)
	{
		ret[i] = (tmp % 10) + 48;
		tmp = tmp / 10;
		i++;
	}
	return (ret);
}

char	*f_itoa(int n)
{
	int				i;
	unsigned int	tmp;
	char			*ret;

	i = 0;
	tmp = n;
	ret = malloc((ft_set_size(n) + 1) * sizeof(char));
	if (ret == NULL)
		return (NULL);
	ret = ft_support(ret, tmp, i, n);
	ret[ft_set_size(n)] = '\0';
	ft_reverse(ret);
	return (ret);
}
