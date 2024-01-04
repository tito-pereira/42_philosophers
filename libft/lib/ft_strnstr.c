/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 11:39:11 by tibarbos          #+#    #+#             */
/*   Updated: 2023/04/28 12:05:13 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (len == 0 && s1[0] == '\0' && s2[0] == '\0')
		return (((char *)s1));
	if (s2[0] == '\0')
		return (((char *)s1));
	while (((char *)s1)[i] != '\0' && i < len)
	{
		while (((char *)s1)[i + j] == s2[j] && s1[i + j] != '\0'
				&& (i + j) < len)
			j++;
		if (len == 0)
			break ;
		if (s2[j] == '\0')
			return (((char *)s1) + i);
		j = 0;
		i++;
	}
	return (NULL);
}

/*int main()
{
    printf("%s\n", ft_strnstr("", "", 0));
}*/

/*
penultimo teste
tem que dar NULL
deu me dolor sit amet

[fail]: your strnstr does not work with empty strings and 0 length

(solved)
if (len == 0)
			break 

erro com empty strings e tamanho zero

According to the C standard, if the substring argument passed to strnstr() 
is an empty string, it will always be found at the start of the searched
string, regardless of the maximum length argument. 
Therefore, the function will return a pointer to the start
of the searched string.

if (!(str = ft_strnstr("lorem ipsum dolor sit amet", "dolor", 15)))
	ft_print_result("NULL");
else
	ft_print_result(str);

strstr, e tipo strchr mas c string
retorna (str + i) caso encontre
retorna NULL caso nao seja encontrado

size e o tamanho que este processo ocorre
a profundidade na s1 que se procura pela s2
como se tratam de strings,
o sizeof vai ser de 1 por serem chars, logo,
size_t = size

strlen == 29, i = 28, i[29] == '\0'

if s2 == \0, retorna s1 ou NULL?
pra ja, retorna s1

s1[i + j] != '\0', faltava esta parte para nao dar segfault
chegava ao \0, eram ambos iguais, e ficava ali preso
se nao existe, da loop infinito?

(((char *)s1) + i)

se nao encontra, chega a s1[i] == '\0'
e da segfault
*/
