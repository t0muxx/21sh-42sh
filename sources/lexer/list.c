/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 04:23:56 by cormarti          #+#    #+#             */
/*   Updated: 2018/05/14 17:11:27 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

void	tkn_push_back(t_tkn **head, t_tkn *new)
{
	t_tkn	*tkn;

	if (new == NULL)
		return ;
	tkn = *head;
	while (tkn->next)
		tkn = tkn->next;
	new->prev = tkn;
	tkn->next = new;
	tkn->next->next = NULL;
}
