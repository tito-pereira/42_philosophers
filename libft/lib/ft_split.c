/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:13:56 by tibarbos          #+#    #+#             */
/*   Updated: 2023/04/29 13:57:18 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_last_o(char *s1, char c)
{
	int	i;

	i = 0;
	while (s1[i] != c && s1[i] != '\0')
		i++;
	if (i < 0)
		i = 0;
	return (i);
}

int	ft_num_o(char *s1, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s1[i] != '\0')
	{
		while (s1[i] == c)
			i++;
		if (s1[i] != c && s1[i] != '\0')
			count++;
		while (s1[i] && s1[i] != c)
			i++;
	}
	return (count);
}

int	ft_fst_o(char *s1, char c)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s1[i] == c)
	{
		i++;
	}
	if (i < 0)
		i = 0;
	return (i);
}

char	**ft_supportt(char **ret, const char *s1, char c, int i)
{
	int		j;
	int		a;
	char	*s2;

	a = 0;
	j = 0;
	s2 = ((char *)s1);
	while (i > 0)
	{
		a = ft_fst_o(((char *)s1), c);
		s2 = ((char *)s1) + (a);
		s1 = s2;
		a = ft_fst_o(((char *)s1), c);
		ret[j] = ft_substr(((char *)s1), 0, ft_last_o(((char *)s1), c));
		s2 = ((char *)s1) + ft_last_o(((char *)s1), c);
		s1 = s2;
		j++;
		i--;
	}
	return (ret);
}

char	**ft_split(char const *s1, char c)
{
	int		i;
	int		n;
	char	**ret;

	n = ft_num_o(((char *)s1), c);
	ret = (char **)malloc((n + 1) * sizeof(char *));
	if (ret == NULL)
		return (NULL);
	i = n;
	ret = ft_supportt(ret, s1, c, i);
	ret[n] = NULL;
	return (ret);
}

/*-----------------------------------------------*/

/*int main()
{
    char    s1[] = "hello!";
    char    c = ' ';
    char    **res;
    int     i = 0;
    res = ft_split(s1, c);
    while (res[i])
        i++;
    printf("---\nres[]: %d+1;\n", i);
    printf("---\n");
    i = 0;
    while (res[i])
    {
        ft_putstr_fd(res[i], 1);
		printf(";\n");
        i++;
    }
	printf("last:%s;\n", res[i]);
	return (0);
}*/

/*

char	**expected:
(char*[6]){"split", "this", "for", "me", "!", NULL};
------------------------------------
entire split

char	*ft_strchrs(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (s + i + 1);
		i++;
	}
	return (NULL);
}

int	ft_num_o(char *s1, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		if (s1[i - 1] == c && s1[i] != c)
			j++;
		i++;
	}
	return (j);
}

int	ft_fst_o(char *s1, char c)
{
	int	i;

	i = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] == c)
		{
			break ;
		}
		i++;
	}
	if (i < 0)
		i = 0;
	return (i);
}

char	**ft_supportt(char **ret, const char *s1, char c, int i)
{
	int		j;
	int		a;
	char	*s2;

	a = 0;
	j = 0;
	s2 = ((char *)s1);
	while (i >= 0)
	{
		s1 = s2;
		a = ft_fst_o(((char *)s1), c);
		if (a != 0)
		{
			ret[j] = ft_substr(((char *)s1), 0, (a));
			s2 = ft_strchrs(((char *)s1), c);
			j++;
		}
		i--;
	}
	return (ret);
}

char	**ft_split(char const *s1, char c)
{
	int		i;
	int		n;
	char	**ret;

	if (s1 == NULL)
		return (NULL);
	n = ft_num_o(((char *)s1), c);
	ret = (char **)malloc((n + 1) * sizeof(char *));
	if (ret == NULL)
		return (NULL);
	i = n;
	ret = ft_supportt(ret, s1, c, i);
	if (n == 0 && ((char *)s1)[0] == '\0')
		ret[n] = '\0';
	ret [n + 1] = '\0';
	return (ret);

----------------------------------
}*/

/*int main()
{
    char    s1[] = "   lorem    ipsum    dolor   ";
    char    c = ' ';
    char    **res;
    int     i = 0;
    res = ft_split(s1, c);
    while (res[i])
        i++;
    printf("---\ni: %d;\n", i);
    printf("---\n");
    i = 0;
    while (res[i])
    {
        ft_putstr_fd(res[i], 1);
		printf(";\n");
        i++;
    }
	return (0);
}*/

/*
	while (i >= 0)
	{
		s1 = s2;
		a = ft_fst_o(((char *)s1), c);
		if (a != 0)
		ret[j] = ft_substr(((char *)s1), 0, (a));
		s2 = ft_strchrs(((char *)s1), c);
		j++;
		i--;
	}

int	ft_num_o(char *s1, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] == c)
			j++;
		i++;
	}
	return (j);
}
o erro agora e o substring em zero talvez
novo erro = ao fazer substring, corta a primeira char*/

/*
Function name ft_split
Prototype char **ft_split(char const *s, char c);
Turn in files -
Parameters s: The string to be split.
c: The delimiter character.
Return value The array of new strings resulting from the split.
NULL if the allocation fails.
External functs. malloc, free
Description Allocates (with malloc(3)) and returns an array
of strings obtained by splitting ’s’ using the
character ’c’ as a delimiter. The array must end
with a NULL pointer.

ideias?
pedem malloc + free...
while i++, if s[i] == c, armazena esse valor de i (malloc)
i = 0, retoma contagem ate ao proximo i
malloc, strdup para pequenas strings

malloc inicial para **ret;
contagem do numero de vezes que c acontece para alocar
o numero de parametros de **return
+ 1 para o '\0', ou NULL;
**ret[0] = *s1, **ret[1] = *s2, **ret[3] = *s3, etc

ou strdup ou substr para criar substrings com
len = distancias entre ocorrencias

substring ate '\0' ou ate s1[i] == c
substring da malloc e copia, fixe
*/
