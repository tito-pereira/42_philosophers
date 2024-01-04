/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 11:08:24 by tibarbos          #+#    #+#             */
/*   Updated: 2023/04/28 13:53:59 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (((char *)str)[i] != '\0')
		i++;
	return (i);
}

/*int main(void)
{
    char    str[] = "123456789012345678901";

    printf("%zu\n", ft_strlen(str));
}*/
