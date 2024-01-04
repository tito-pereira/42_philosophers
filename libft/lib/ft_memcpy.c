/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 11:32:06 by tibarbos          #+#    #+#             */
/*   Updated: 2023/04/28 11:23:11 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t len)
{
	size_t	i;

	if (dest == NULL && src == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

/*int main()
{
    char    s1[30];
    char    s2[] = "wassup peeps";
    printf("%s\n", ft_memcpy(s1, s2, 6));
}*/

/*
[crash]: your memcpy does not behave well with NULL as both params with size


[crash]: your memcpy does not behave well with NULL as both params with size
 Test code:
 	ft_memcpy(((void*)0), ((void*)0), 3);

era literalmente isto, mas nao meter o '\0' no fim
podem ser ints, nao sao so strings
memcpy
(memcpy cannot handle overlap)
strcpy s1, s2
adicionar '\0' a s1[i]
apenas fez while len--,
s1 = s2
o chatgpt fez algo do genero, nao acrescentou o '\0'
nao quer mexer nos '\0' pelos vistos para nao alterar as memorias

memmove
(memmove can handle overlap)
if (dest < src)
strcpy, s1, s2, i < n, i++;

else (dest >= src)
(i = n, i > 0, i--);

o processo e o mesmo, apenas queremos garantir que nao copiamos
a mais para a pasta dest, nao acrescentamos memoria um ao outro

se calhar so se usa o memcpy quando nao ha overlaps
para garantir que nao ha overlaps de memoria
talvez o memmove tenha que usar um malloc
para nao alterar a memoria um do outro

void *memcpy(void *dest, const void *src, size_t len)
*/
