/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 12:28:18 by tibarbos          #+#    #+#             */
/*   Updated: 2023/04/26 13:17:03 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(void *s1, void *s2, size_t n)
{
	unsigned char	*a;
	unsigned char	*b;
	size_t			i;

	i = 0;
	a = s1;
	b = s2;
	while (i < n)
	{
		if (a[i] > b[i])
			return (1);
		if (a[i] < b[i])
			return (-1);
		i++;
	}
	return (0);
}

/*int main()
{
    size_t  n = 2;
    char    s3[] = "hello";
    char    s4[] = "helso";
    printf("memcmp test: %d\n", ft_memcmp(s3, s4, n));
}*/

/*
tenho que comparar sempre em unsign pq sao blocos de memoria
mas tenho q retornar zero ou -1,*/
/*&& ((unsigned char *)s1)[i] && ((unsigned char *)s2)[i] 
isalpha
usar strcmp entre aqueles blocos de memoria
e com um len definido
int memcmp(const void* ptr1, const void* ptr2, size_t num)
*/
