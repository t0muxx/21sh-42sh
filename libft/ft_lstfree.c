/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 08:52:22 by tmaraval          #+#    #+#             */
/*   Updated: 2018/10/15 10:18:50 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstfree(t_list *head)
{
	t_list *temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->content);
		free(temp);
		temp = NULL;
	}
	head = NULL;
}
