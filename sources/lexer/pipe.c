/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 01:48:54 by cormarti          #+#    #+#             */
/*   Updated: 2018/05/15 17:17:17 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

static t_tkn	*tkn_or_if(char **str)
{
	t_tkn	*tkn;
	char	*line;

	line = *str;
	tkn = tkn_init(2);
	tkn->data = ft_strncpy(tkn->data, line, 2);
	tkn->type = CHR_OR_IF;
	line += 2;
	*str = line;
	return (tkn);
}

t_tkn			*tkn_pipe(char **str)
{
	t_tkn	*tkn;
	char	*line;

	line = *str;
	if (*(line + 1) == '|')
		tkn = tkn_or_if(&line);
	else
	{
		tkn = tkn_init(1);
		tkn->data[0] = '|';
		tkn->type = CHR_PIPE;
		line++;
	}
	*str = line;
	return (tkn);
}
