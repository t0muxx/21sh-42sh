/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 08:36:36 by tmaraval          #+#    #+#             */
/*   Updated: 2018/02/13 08:46:50 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_free(t_list *list)
{
	t_list *temp;

	while (list)
	{
		temp = list;
		list = list->next;
		free(temp->content);
		free(temp);
		temp = NULL;
	}
	list = NULL;
}
