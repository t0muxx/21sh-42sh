/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 01:52:11 by cormarti          #+#    #+#             */
/*   Updated: 2018/09/16 00:49:10 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

t_tkn	*tkn_init(int len)
{
	t_tkn	*tkn;

	tkn = NULL;
	if (!(tkn = (t_tkn*)malloc(sizeof(t_tkn)))
			|| !(tkn->data = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	tkn->data[len] = '\0';
	tkn->type = CHR_NULL;
	tkn->next = NULL;
	tkn->prev = NULL;
	return (tkn);
}

t_tkn	*tkn_init_nl(void)
{
	t_tkn	*tkn;

	tkn = NULL;
	if (!(tkn = (t_tkn*)malloc(sizeof(t_tkn)))
			|| !(tkn->data = (char*)malloc(sizeof(char) * (2))))
		return (NULL);
	tkn->data[0] = '\n';
	tkn->data[1] = '\0';
	tkn->type = CHR_NEWLINE;
	tkn->next = NULL;
	tkn->prev = NULL;
	return (tkn);
}
