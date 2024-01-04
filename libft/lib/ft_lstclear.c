/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 12:45:37 by tibarbos          #+#    #+#             */
/*   Updated: 2023/04/25 17:59:21 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;

	while ((*lst) != NULL)
	{
		tmp = (*lst)->next;
		if (del != NULL)
			del((*lst)->content);
		free((*lst));
		(*lst) = tmp;
	}
}

/*
void	lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;

	if (lst == NULL || *lst == NULL)
		return ;
	while (*lst != NULL)
	{
		temp = (*lst)->next;
		if (del != NULL)
			del((*lst)->content);
		free(*lst);
		*lst = temp;
		pq q adicionar este tmp acabou c os erros
		(tamos a guardar o proximo pointer, dar free e dp tentar usar
		um pointer q ja demos free
		na delone igual)
	}
	while ((*lst) != NULL)
	{
		if (del != NULL)
			del((*lst)->content);
		free((*lst));
		(*lst) = (*lst)->next;
	}
	while (tmp != NULL)
	{
		del(tmp->content);
		tmp = tmp->next;
	}
}
*/

/*
Turn in files -
Parameters lst: The address of a pointer to a node.
del: The address of the function used to delete
the content of the node.
Return value None
External functs. free
Description Deletes and frees the given node and every
successor of that node, using the function ’del’
and free(3).
Finally, the pointer to the list must be set to
NULL.
*/
