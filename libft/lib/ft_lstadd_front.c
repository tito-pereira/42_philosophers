/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tibarbos <tibarbos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 12:43:09 by tibarbos          #+#    #+#             */
/*   Updated: 2023/04/25 18:09:40 by tibarbos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

/*
*/

/*
lst - The address of a pointer to the first link of
a list.
new - The address of a pointer to the node to be
added to the list.
Return value - None
External functs - None
Description - Adds the node ’new’ at the beginning of the list.

erro
(*lst)->next = new
*/
