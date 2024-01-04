/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 12:43:56 by tibarbos          #+#    #+#             */
/*   Updated: 2023/04/25 17:00:19 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

/*int	main()
{}
*/

/*
Turn in files -
Parameters lst: The beginning of the list.
Return value Last node of the list
External functs. None
Description Returns the last node of the list.

erros corrigidos
.em vez de while (lst != NULL), lst->next != NULL
senao o while quebra quando a lst em si e nulo
.proteger o return, is lst == NULL, return NULL
*/
