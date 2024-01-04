/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 12:46:00 by tibarbos          #+#    #+#             */
/*   Updated: 2023/04/25 17:49:02 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst != NULL)
	{
		f(lst->content);
		lst = lst->next;
	}
}

/*int	main()
{}
*/

/*
Turn in files -
Parameters lst: The address of a pointer to a node.
f: The address of the function used to iterate on
the list.
Return value None
External functs. None
Description Iterates the list ’lst’ and applies the function
’f’ on the content of each node.
*/
