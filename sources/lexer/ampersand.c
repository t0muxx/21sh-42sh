/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ampersand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 01:55:42 by cormarti          #+#    #+#             */
/*   Updated: 2018/09/06 17:30:09 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

static t_tkn	*tkn_and_dgreat(char **str)
{
	t_tkn	*tkn;
	char	*line;

	line = *str;
	tkn = tkn_init(3);
	tkn->data = ft_strncpy(tkn->data, line, 3);
	tkn->type = CHR_ANDDGREAT;
	line += 3;
	*str = line;
	return (tkn);
}

static t_tkn	*tkn_and_great(char **str)
{
	t_tkn	*tkn;
	char	*line;

	line = *str;
	tkn = tkn_init(2);
	tkn->data = ft_strncpy(tkn->data, line, 2);
	tkn->type = CHR_ANDGREAT;
	line += 2;
	*str = line;
	return (tkn);
}
static t_tkn	*tkn_and_if(char **str)
{
	t_tkn	*tkn;
	char	*line;

	line = *str;
	tkn = tkn_init(2);
	tkn->data = ft_strncpy(tkn->data, line, 2);
	tkn->type = CHR_AND_IF;
	line += 2;
	*str = line;
	return (tkn);
}

t_tkn			*tkn_and(char **str)
{
	t_tkn	*tkn;
	char	*line;

	line = *str;
	if (*(line + 1) == '&')
		tkn = tkn_and_if(&line);
	else if (*(line + 1) == '>')
	{
		if (*(line + 2) == '>')
			tkn = tkn_and_dgreat(&line);
		else
			tkn = tkn_and_great(&line);
	}
	else
	{
		line = *str;
		tkn = tkn_init(1);
		tkn->data[0] = '&';
		tkn->type = CHR_AND;
		line++;
	}
	*str = line;
	return (tkn);
}
