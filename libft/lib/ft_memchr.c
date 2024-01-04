/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 12:28:06 by tibarbos          #+#    #+#             */
/*   Updated: 2023/04/26 12:01:59 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t len)
{
	size_t			i;

	i = 0;
	while (i < len)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return (((void *)s) + i);
		i++;
	}
	return (NULL);
}

/*int main()
{
    unsigned int	s1[] = {1, -4, 5, -3, 0, 3, 4, 5};
    unsigned int	c = 0 + 256;
	unsigned int	*s2 = ft_memchr(s1, c, 2);
	printf("%d\n%d\n%d\n", s2[0], s2[1], s2[2]);
}*/

/*
passar tanto o s como o c a unsigned char

3 args, str void*, int c, size_t len
strchr, retorna a str a partir da 1st occorencia de c
dentro de um limite de len
senao, retorna nulo
*/
