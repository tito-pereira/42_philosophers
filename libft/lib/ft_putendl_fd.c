/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 11:13:32 by tibarbos          #+#    #+#             */
/*   Updated: 2023/04/24 20:13:53 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		write (fd, &s[i], 1);
		i++;
	}
	write (fd, "\n", 1);
}

/*int main()
{
    char    str[] = "testtest";
    ft_putendl_fd(str);
}*/

/*
[fail]: your putendl_fd does not work with basic input
[fail]: your putendl_fd does not work with non ascii chars

pode se usar write
Outputs the string ’s’ to the given file descriptor
followed by a newline
s: The string to output.
fd: The file descriptor on which to write.
*/
