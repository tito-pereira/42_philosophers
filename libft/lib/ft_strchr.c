/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:48:47 by tibarbos          #+#    #+#             */
/*   Updated: 2023/04/28 12:35:51 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

/*int main()
{
    char    s[] = "teste";
    char    a = 'a';
    printf("%s\n", ft_strchr(s, a));
}*/

/*

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (((unsigned char *)s)[i])
	{
		if (s[i] == c)
			return (s + i);
		i++;
	}
	if (s[0] == '\0' && c != '\0')
		return (NULL);
	if (s[i] == '\0' && c == '\0')
		return ("\0");
	return (NULL);
}
[fail]: your strchr does not work with \0
[solve]: while (s[i] >= 0 && s[i] <= 126)
em vez de ate != '\0'
Error in test 3: ft_strchr(0x557f25cc60a6: "teste", 0: '\0'): expected: 
0x557f25cc60ab, yours: (nil)
Error in test 6: ft_strchr(0x557f25cc60a6: "teste", 1024: '\0'): expected: 
0x557f25cc60ab, yours: (nil)
meter a funcionar ate encontrar \0

"teste", 'a' (null), meu \0
"teste", 'e' (0), meu null
"teste", '\0' (0), meu null
The first argument of strchr should be a string, represented as a pointer 
to its first character. The value 0x558c070ce020 in your example looks like
a memory address, but it is not clear what data is stored at that address.

Assuming that 0x558c070ce020 is actually a valid pointer to the string "teste",
and that the second argument 357 is an integer representing the ASCII value
of the character 'e', then the function call 
strchr(0x558c070ce020: "teste", 357: 'e')
would search the string "teste" for the character with ASCII value 357.

However, the ASCII table only defines values for characters up to 127.
An ASCII value of 357 is not a valid ASCII code point, so it is not clear 
what character the function is intended to search for.

Assuming that 357 was a mistake and was intended to be the ASCII value
of the character 'e', the function call would return a pointer to the 
first occurrence of the character 'e' in the string "teste", or NULL if
the character is not found. The return value would be a pointer to the 
memory location where the character 'e' is stored in the string.

procura a primeira ocorrencia de c
em toda a string s, retorna a string a partir dai
retorna NULL if not found

ultimos dois testes
t5 e t6, deram me null era suposto dar 0, ou o oposto

5 if (!(str = ft_strchr(str2, '\0')))
			ft_print_result("NULL");
		else
		{
			ft_print_result(str);
			if (str != str2 + 7)
				ft_print_result("\nReturn value is false");
		}

deve retornar um pointer para '\0'
(o '\0' no fim de bonour e o '\0' da s2)

6 char	str3[] = "";
		if (!(str = ft_strchr(str3, '\0')))
			ft_print_result("NULL");
		else
		{
			ft_print_result(str);
			if (str != str3)
				ft_print_result("\nReturn value is false");
		}
*/
