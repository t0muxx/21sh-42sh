/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   great.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 03:59:29 by cormarti          #+#    #+#             */
/*   Updated: 2018/03/31 02:05:30 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

static t_tkn	*tkn_clobber(char **str)
{
	t_tkn	*tkn;
	char	*line;

	line = *str;
	tkn = tkn_init(2);
	tkn->data = ft_strncpy(tkn->data, line, 2);
	tkn->type = CHR_CLOBBER;
	line += 2;
	*str = line;
	return (tkn);
}

static t_tkn	*tkn_greatand(char **str)
{
	t_tkn	*tkn;
	char	*line;

	line = *str;
	tkn = tkn_init(2);
	tkn->data = ft_strncpy(tkn->data, line, 2);
	tkn->type = CHR_GREATAND;
	line += 2;
	*str = line;
	return (tkn);
}

static t_tkn	*tkn_dgreat(char **str)
{
	t_tkn	*tkn;
	char	*line;

	line = *str;
	tkn = tkn_init(2);
	tkn->data = ft_strncpy(tkn->data, line, 2);
	tkn->type = CHR_DGREAT;
	line += 2;
	*str = line;
	return (tkn);
}

t_tkn			*tkn_great(char **str)
{
	t_tkn	*tkn;
	char	*line;

	line = *str;
	if (*(line + 1) == CHR_GREAT)
		tkn = tkn_dgreat(&line);
	else if (*(line + 1) == CHR_AND)
		tkn = tkn_greatand(&line);
	else if (*(line + 1) == CHR_PIPE)
		tkn = tkn_clobber(&line);
	else
	{
		tkn = tkn_init(1);
		tkn->type = CHR_GREAT;
		ft_strncpy(tkn->data, line, 1);
		line++;
	}
	*str = line;
	return (tkn);
}
