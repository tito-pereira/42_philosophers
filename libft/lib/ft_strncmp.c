/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 11:39:57 by tibarbos          #+#    #+#             */
/*   Updated: 2023/04/24 14:43:15 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(char *s1, char *s2, unsigned int size)
{
	while ((*s1 != '\0' || *s2 != '\0') && *s1 == *s2 && size > 0)
	{
		s1++;
		s2++;
		size--;
	}
	if (size == 0)
		return (0);
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

/*int main()
{
    printf("result: %d\n", ft_strncmp("test\200", "test\0", 6));
}*/

/*
else if (arg == 9)
	ft_print_result(ft_strncmp("zyxbcdefgh", "abcdwxyz", 0));, deu me 25(1);
else if (arg == 10)
	ft_print_result(ft_strncmp("abcdefgh", "", 0)); deu me 97 (1);
else if (arg == 11)
	ft_print_result(ft_strncmp("test\200", "test\0", 6)); deu me -128 (-1);

	nao percebo o erro nos testes

9 tem que dar 0, deu me 1
10 tem que dar 0, deu me 1
solved com aquele if
11 tem que dar 1, deu me -1

chatgpt diz que deve retornar negativo
teste diz que deve retornar positivo

1: positivo
0: 
-1: negativo
*/