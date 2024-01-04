/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:49:11 by tibarbos          #+#    #+#             */
/*   Updated: 2023/04/28 12:46:08 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned int	i;

	i = 0;
	while (((char *)s)[i] != '\0')
		i++;
	if (((char *)s)[i] == (unsigned char)c)
		return (((char *)s) + i);
	while (i)
	{
		i--;
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return (((char *)s) + i);
	}
	return (NULL);
}

/*int main()
{
    char    s[] = "wassup ladies and germs";
	char    a = 357: 'e';
    printf("%s\n", ft_strrchr("teste", a));
}*/

/*
char	*ft_strchr(char *s, int c)
{
	unsigned int	i;

	i = 0;
	if (s[i] == '\0' && c == '\0')
		return (s + i);
	while (s[i] != '\0')
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return (s + i);
		i++;
	}
	if ((unsigned char)c == '\0')
		return (s + i);
	return (NULL);
}
Error in test 4: ft_strchr(0x55d1a021c0a6: "teste", 97: 'a'): expected: (nil), 
yours: 0x55d1a021c0f4
Error in test 5: ft_strchr(0x55d1a021c0a6: "teste", 357: 'e'): expected: 
0x55d1a021c0a7, yours: (nil)
Error in test 6: ft_strchr(0x55d1a021c0a6: "teste", 1024: '\0'): expected: 
0x55d1a021c0ab, yours: (nil)

erro 4, se nao encontrar, retorna NULL
*/