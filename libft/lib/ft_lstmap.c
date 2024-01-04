/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 12:46:33 by tibarbos          #+#    #+#             */
/*   Updated: 2023/04/28 16:24:49 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*nlist;
	t_list	*new;

	if (f == NULL || lst == NULL || del == NULL)
		return (NULL);
	new = ft_lstnew(f(lst->content));
	if (new == NULL)
		ft_lstdelone(lst->content, del);
	nlist = new;
	lst = lst->next;
	while (lst != NULL)
	{
		new = ft_lstnew(f(lst->content));
		if (new == NULL)
			ft_lstdelone(lst->content, del);
		ft_lstadd_back(&nlist, new);
		lst = lst->next;
	}
	return (nlist);
}

/*t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
    t_list *new_elem;
    t_list **new_list_ptr;
	
    new_elem = (t_list *)malloc(sizeof(t_list));
	while (lst != NULL)
	{
        new_elem->content = f(lst->content);
		del(lst->content);
		free (lst->content);
        new_elem->next = NULL;
        *new_list_ptr = new_elem;
        new_list_ptr = &(new_elem->next);
        lst = lst->next;
    }
    return new_elem;
}*/

/*t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_elem;

	if (!lst || !f)
		return (NULL);
	if (!(new_elem = ft_lstnew(f(lst->content))))
	{
		ft_lstclear(&lst, del);
		return (NULL);
	}
	new_lst = new_elem;
	lst = lst->next;
	while (lst)
	{
		if (!(new_elem = ft_lstnew(f(lst->content))))
		{
			ft_lstclear(&lst, del);
			ft_lstclear(&new_lst, del);
			break ;
		}
		lst = lst->next;
		ft_lstadd_back(&new_lst, new_elem);
	}
	return (new_lst);
}*/

/*Turn in files -
Parameters lst: The address of a pointer to a node.
f: The address of the function used to iterate on
the list.
del: The address of the function used to delete
the content of a node if needed.
Return value The new list.
NULL if the allocation fails.

malloc, free

Description Iterates the list ’lst’ and applies the function
’f’ on the content of each node. Creates a new
list resulting of the successive applications of
the function ’f’. The ’del’ function is used to
delete the content of a node if needed.

endereco nulo
como copiar (malloc e copy)
como saber quando apagar ou iterar
*/
