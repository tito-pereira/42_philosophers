/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 19:53:26 by tibarbos          #+#    #+#             */
/*   Updated: 2023/04/24 14:18:40 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	void	*bbc;
	size_t	len;
	size_t	i;

	i = 0;
	len = num * size;
	bbc = malloc(len);
	if (!bbc)
		return (NULL);
	while (i < len)
	{
		((unsigned char *)bbc)[i] = '\0';
		i++;
	}
	return (bbc);
}

/*int main()
{
    printf("%s\n", (unsigned char *)ft_calloc(5, 1));
    return (0);
}*/

/*int		main()
{
	char	*str;

	str = (char *)ft_calloc(30, 1);
	if (!str)
		write(1, "NULL", 4);
	else
		write(1, str, 30);
	printf("\n");
	return (0);
}*/

/*
questao do '\0' no final
bbc[i] = '\0';
*/
