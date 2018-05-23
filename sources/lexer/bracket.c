/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bracket.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 01:04:24 by cormarti          #+#    #+#             */
/*   Updated: 2018/05/15 17:19:43 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

t_tkn	*tkn_lbracket(char **str)
{
	t_tkn	*tkn;
	char	*line;

	line = *str;
	tkn = tkn_init(1);
	tkn->data[0] = '(';
	tkn->type = CHR_LBRACKET;
	line++;
	*str = line;
	return (tkn);
}

t_tkn	*tkn_rbracket(char **str)
{
	t_tkn	*tkn;
	char	*line;

	line = *str;
	tkn = tkn_init(1);
	tkn->data[0] = ')';
	tkn->type = CHR_RBRACKET;
	line++;
	*str = line;
	return (tkn);
}
