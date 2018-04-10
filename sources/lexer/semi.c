/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 01:10:07 by cormarti          #+#    #+#             */
/*   Updated: 2018/03/31 01:28:27 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

static t_tkn	*tkn_is_dsemi(char **str)
{
	t_tkn	*tkn;
	char	*line;

	line = *str;
	tkn = tkn_init(2);
	tkn->data = ft_strncpy(tkn->data, line, 2);
	tkn->type = CHR_DSEMI;
	line += 2;
	*str = line;
	return (tkn);
}

t_tkn			*tkn_semi(char **str)
{
	t_tkn	*tkn;
	char	*line;

	line = *str;
	if (*(line + 1) == CHR_SEMI)
		tkn = tkn_is_dsemi(&line);
	else
	{
		tkn = tkn_init(1);
		tkn->data[0] = CHR_SEMI;
		tkn->type = CHR_SEMI;
		line++;
	}
	*str = line;
	return (tkn);
}
