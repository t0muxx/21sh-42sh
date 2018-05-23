/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 01:50:19 by cormarti          #+#    #+#             */
/*   Updated: 2018/05/15 17:21:35 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

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
