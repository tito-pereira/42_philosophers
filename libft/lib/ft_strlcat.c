/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 11:26:19 by tibarbos          #+#    #+#             */
/*   Updated: 2023/04/26 14:37:00 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	ret;
	size_t	restsize;

	ret = ft_strlen(dest) + ft_strlen(((char *)src));
	if (size == 0 || size <= ft_strlen(dest))
		return (ft_strlen((char *)src) + size);
	j = 0;
	i = ft_strlen(dest);
	restsize = size - i;
	while (((char *)src)[j] != '\0' && j < restsize - 1)
	{
		dest[i] = ((char *)src)[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (ret);
}

/*int main()
{
    char    s1[10];
    char    s2[] = "lorem ipsum dolor sit amet";
	s1[10] = 'a';
	printf("return: %ld\n", ft_strlcat(s1, s2, 6));
    printf("dest: %s\n", s1);
}*/

/*
Test 8:
    dest[10] = 'a';
    ft_print_result(ft_strlcat(dest, "lorem ipsum dolor sit amet", 6));
    write(1, "\n", 1);
    write(1, dest, 15);
Expected (cat -e test08.output):
32$
rrrrrr^@^@^@^@a^@^@^@^@
Your result (cat -e user_output_test08):
32$
rrrrrrlorem ips

concatenar s1 e s2, strcat;
size, limita o size da dest
e o tamanho que queremos que a string dest tenha
s1 = 6, i=7
s2 = 6, i=7

o segundo retorno ta mal
a char *dest modifica se

return e o comprimento da string que iria ser formada
ha retornos diferentes okok

size = 0, size <= dlen
nao ha strcat
retorno = slen + size

size > dlen
o segundo e dlen + slen
*/