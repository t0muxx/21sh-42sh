/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 01:00:40 by cormarti          #+#    #+#             */
/*   Updated: 2018/05/15 17:19:31 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

t_tkn	*tkn_lbrace(char **str)
{
	t_tkn	*tkn;
	char	*line;

	line = *str;
	tkn = tkn_init(1);
	tkn->data[0] = '{';
	tkn->type = CHR_LBRACE;
	line++;
	*str = line;
	return (tkn);
}

t_tkn	*tkn_rbrace(char **str)
{
	t_tkn	*tkn;
	char	*line;

	line = *str;
	tkn = tkn_init(1);
	tkn->data[0] = '}';
	tkn->type = CHR_RBRACE;
	line++;
	*str = line;
	return (tkn);
}
