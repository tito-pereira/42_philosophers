/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 12:17:34 by tibarbos          #+#    #+#             */
/*   Updated: 2023/04/28 11:21:31 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	size_t	i;

	if (dest == NULL && src == NULL)
		return (NULL);
	i = 0;
	if (dest < src)
	{
		while (i < len)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	else
	{
		i = len;
		while (i > 0)
		{
			((unsigned char *)dest)[i - 1] = ((unsigned char *)src)[i - 1];
			i--;
		}
	}
	return (dest);
}

/*void *ft_memmove(void *dst, const void *src, size_t n) {
    char *d = dst;
    const char *s = src;
    if (d < s) {
        for (size_t i = 0; i < n; i++) {
            d[i] = s[i];
        }
    } else {
        for (size_t i = n; i > 0; i--) {
            d[i-1] = s[i-1];
        }
    }
    return dst;
}*/

/*int main()
{
    char    s1[30];
    char    s2[] = "hello";
	int		i = 5;
    printf("%s\n", ft_memmove(s1, s2, i));
}*/

/*The function checks whether the destination memory block comes
before or after the source memory block in memory. If the 
destination block comes before the source block, the function 
copies the memory block from beginning to end. If the destination 
block comes after the source block, the function copies the memory
block from end to beginning, to avoid overlapping 
the memory being copied. 

strcpy s1, s2
adicionar '\0' a s1[i]

Note that memmove() is different from memcpy()
in that it can handle overlapping memory areas, while memcpy() cannot.

void *memmove(void *dest, const void *src, size_t len)

memmove can handle overlap
memcpy cannot handle overlap

If the source and destination memory areas do not overlap,
both functions can be used interchangeably
*/
