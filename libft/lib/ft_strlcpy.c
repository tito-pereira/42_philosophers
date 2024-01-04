/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 11:26:33 by tibarbos          #+#    #+#             */
/*   Updated: 2023/04/26 13:20:14 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *s1, const char *s2, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s2[j] != '\0')
		j++;
	if (size == 0)
		return (j);
	if (size > 0)
	{
		while (s2[i] != '\0' && i < (size - 1))
		{
			s1[i] = s2[i];
			i++;
		}
		s1[i] = '\0';
	}
	return (j);
}

/*int main()
{
    char    *s1;
    char    s2[] = "12345678";
    int i = 3;

    s1 = malloc(sizeof(s2));
    printf("%ld\n", ft_strlcpy(s1, s2, i));
    ft_strlcpy(s1, s2, i);
    printf("%s\n", s1);
}*/

/*
size - 1 em vez de size

passar a (unsign char *) para ter mais memoria?idk

o return e a strlen da string que ira ser
formada, isto e, o strlen(source)
o size ja inclui o nulo, isto e, size = 4
significa 3 chars
e o numero de chars que queremos na string
final, isto e, na dest
size ou (size - 1)
o size deve ser 3 nao?
*/
