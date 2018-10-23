/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsortedinsert.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 09:02:30 by tmaraval          #+#    #+#             */
/*   Updated: 2018/10/15 10:19:06 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_sortedinsert(t_list **last, t_list *new_node)
{
	t_list	*current;

	if (*last == NULL || ft_strcmp((*last)->content, new_node->content) >= 0)
	{
		new_node->next = *last;
		*last = new_node;
	}
	else
	{
		current = *last;
		while (current->next != NULL &&
		ft_strcmp(current->next->content, new_node->content) < 0)
		{
			current = current->next;
		}
		new_node->next = current->next;
		current->next = new_node;
	}
}
