/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 01:50:19 by cormarti          #+#    #+#             */
/*   Updated: 2018/11/20 14:18:47 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

int		is_quote(int chr, t_tkn_state state)
{
	if (chr == '"')
		return (state == STATE_QUOTED ? 0 : 1);
	else if (chr == '\'')
		return (state == STATE_DQUOTED ? 0 : 1);
	else
		return (0);
}

t_tkn	*tkn_bquote(char **str)
{
	t_tkn	*tkn;
	char	*line;

	line = *str;
	tkn = tkn_init(1);
	tkn->data[0] = '`';
	tkn->type = CHR_BQUOTE;
	line++;
	*str = line;
	return (tkn);
}

t_tkn	*tkn_dquote(char **str)
{
	t_tkn	*tkn;
	char	*line;

	line = *str;
	tkn = tkn_init(1);
	tkn->data[0] = '"';
	tkn->type = CHR_DQUOTE;
	line++;
	*str = line;
	return (tkn);
}

t_tkn	*tkn_quote(char **str)
{
	t_tkn	*tkn;
	char	*line;

	line = *str;
	tkn = tkn_init(1);
	tkn->data[0] = '\'';
	tkn->type = CHR_QUOTE;
	line++;
	*str = line;
	return (tkn);
}
