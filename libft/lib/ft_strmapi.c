/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:14:57 by tibarbos          #+#    #+#             */
/*   Updated: 2023/04/25 09:49:18 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*char	ft_test(unsigned int i, char c)
{
	c = c + i;
	return (c);
}*/

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	len;
	char			*res;

	i = 0;
	len = ft_strlen(((char *)s));
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (((char *)s)[i] != '\0')
	{
		res[i] = f(i, ((char *)s)[i]);
		i++;
	}
	res[i] = '\0';
	return (res);
}

/*int main()
{
    char    str[] = "wassup";
    printf("res: %s;\n", ft_strmapi(str, ft_test));
}*/

/*
usa pointers para funcoes

s: The string on which to iterate.
f: The function to apply to each character

return - the string created from the successive applications
of ’f’.
return - NULL if the allocation fails.
aplica as alteracoes numa nova string criada com malloc;
ou seja, um strdup;

Applies the function ’f’ to each character of the
string ’s’, and passing its index as first argument
to create a new string (with malloc(3)) resulting
from successive applications of ’f’.
*/
