/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:15:05 by tibarbos          #+#    #+#             */
/*   Updated: 2023/04/28 13:09:42 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_sup(char *substr, char const *s, unsigned int start, size_t len)
{
	size_t	i;

	i = 0;
	while (s[start] != '\0' && len > 0)
	{
		substr[i] = s[start];
		start++;
		i++;
		len--;
	}
	substr[i] = '\0';
	return (substr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*substr;

	if (len >= ft_strlen(((char *)s)))
		len = ft_strlen(((char *)s)) - start;
	if (start >= ft_strlen(((char *)s)))
	{
		substr = malloc(1 * sizeof(char));
		substr[0] = '\0';
		return (substr);
	}
	else
		substr = malloc((len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	substr = ft_sup(substr, ((char *)s), start, len);
	return (substr);
}

/*int main()
{
    char    s[] = "uma duas tres palavras";
    int start = 4;
    size_t  len = 127635;
    printf("%s\n", ft_substr(s, start, len));
}*/

/*
[fail]: your substr does not work when start >= ft_strlen(s)
Error in test 5: ft_substr("hola", 0, 18446744073709551615): not enough memory 
allocated, needed: 5, reserved: 0
Error in test 5: ft_substr("hola", 0, 18446744073709551615): 
Memory leak: 0x561a7c72e8b0 - 8192 bytes
You failed to free the memory allocated at:

com malloc cria uma substring
retorna essa string a partir do start
e com len maximo de tamanho
retorna NULL se nao houver nada

len, size t, = size * sizeof*/
