/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:14:43 by tibarbos          #+#    #+#             */
/*   Updated: 2023/04/26 11:38:29 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	if (f != NULL)
	{
		if (s != NULL)
		{
			while (s[i] != '\0')
			{
				f(i, (s + i));
				i++;
			}
		}
	}
}

/*int main()
{
    char    str[] = "l0rem ipsum";
    ft_striteri(str, iter);
    printf("res: %s;\n", str);
}*/

/*
tinha f(i, s), e f(i, s[i]) e era essa a ideia claramente
mas

usa pointers para funcoes

s: The string on which to iterate.
f: The function to apply to each character.

return, ext functions - none;
aplica as alteracoes na propria string;

Applies the function ’f’ on each character of
the string passed as argument, passing its index
as first argument. Each character is passed by
address to ’f’ to be modified if necessary.
*/
