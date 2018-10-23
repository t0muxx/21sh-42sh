/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 09:33:15 by tmaraval          #+#    #+#             */
/*   Updated: 2017/11/20 08:09:18 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *list;

	if (lst == NULL)
		return (NULL);
	if ((list = (t_list*)malloc(sizeof(f(lst)))) == NULL)
		return (NULL);
	list = f(lst);
	list->next = ft_lstmap(lst->next, f);
	return (list);
}
