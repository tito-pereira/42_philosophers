/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:18:10 by tibarbos          #+#    #+#             */
/*   Updated: 2023/04/28 18:59:12 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_count(char s1, char *s2)
{
	unsigned int	i;

	i = 0;
	while (s2[i] != '\0')
	{
		if (s1 == s2[i])
			return (2);
		i++;
	}
	return (1);
}

char	*ft_str_rev(char *str)
{
	int		size;
	int		i;
	char	tmp;

	i = 0;
	tmp = '0';
	size = ft_strlen(str);
	while (i < (size / 2))
	{
		tmp = str[i];
		str[i] = str[size - 1 - i];
		str[size - 1 - i] = tmp;
		i++;
	}
	return (str);
}

unsigned int	ft_start_i(char *s1, char *s2)
{
	unsigned int	i;

	i = 0;
	while (ft_count(s1[i], s2) == 2)
	{
		i++;
	}
	return (i);
}

int	ft_last_i(char *s1, char *set)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	i = ft_strlen(s1);
	ft_str_rev(s1);
	ft_str_rev(set);
	j = ft_start_i(s1, set);
	ft_str_rev(s1);
	ft_str_rev(set);
	return (i - j);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	startindex;
	int		len;
	char	*trim;
	char	*a;
	char	*b;

	a = ft_strdup(((char *)s1));
	b = ft_strdup(((char *)set));
	if (a == NULL || b == NULL)
		return (NULL);
	startindex = ft_start_i(a, b);
	len = ft_last_i(a, b) - startindex;
	free (a);
	free (b);
	if (len <= 0)
	{
		trim = (char *)malloc(1 * sizeof(char));
		trim[0] = '\0';
		return (trim);
	}
	trim = ft_substr(s1, startindex, len);
	if (trim == NULL)
		return (NULL);
	return (trim);
}

/*int main()
{
	char	s1[] = "   \t  \n\n \t\t  \n\n\nHello
	\t  Please\n Trim me !\n   \n \n \t\t\n  ";
	char	s2[] = " \n\t";
    printf("(trim)%s(trim)\n", ft_strtrim(s1, s2));
}*/

/*
[crash]: you dont protect your malloc return


[crash]: you dont protect your malloc return
 Test code:
 	char *s1 = "   \t  \n\n \t\t  \n\n\nHello \t
	  Please\n Trim me !\n   \n \n \t\t\n  ";
 
 	char *ret = ft_strtrim(s1, " \n\t");
 	if (ret == ((void*)0))
 		exit(TEST_SUCCESS);
 	exit(TEST_FAILED);

malloc
s1: The string to be trimmed.
set: The reference set of characters to trim
return - The trimmed string.
     - NULL if the allocation fails
Allocates (with malloc(3)) and returns a copy of
’s1’ with the characters specified in ’set’ removed
from the beginning and the end of the string.
*/
