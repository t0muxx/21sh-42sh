/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   less.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 23:21:08 by cormarti          #+#    #+#             */
/*   Updated: 2018/06/23 17:50:47 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

static t_tkn	*tkn_is_dlessdash(char **str)
{
	t_tkn	*tkn;
	char	*line;

	line = *str;
	tkn = tkn_init(3);
	tkn->type = CHR_DLESSDASH;
	ft_strncpy(tkn->data, line, 3);
	line += 3;
	*str = line;
	return (tkn);
}

static t_tkn	*tkn_is_dless(char **str)
{
	t_tkn	*tkn;
	char	*line;

	line = *str;
	tkn = tkn_init(2);
	tkn->type = CHR_DLESS;
	ft_strncpy(tkn->data, line, 2);
	line += 2;
	*str = line;
	return (tkn);
}

static t_tkn	*tkn_is_lessand(char **str)
{
	t_tkn	*tkn;
	char	*line;

	line = *str;
	tkn = tkn_init(2);
	tkn->type = CHR_LESSAND;
	ft_strncpy(tkn->data, line, 2);
	line += 2;
	*str = line;
	return (tkn);
}

static t_tkn	*tkn_is_less(char **str)
{
	t_tkn	*tkn;
	char	*line;

	line = *str;
	tkn = tkn_init(1);
	tkn->type = CHR_LESS;
	ft_strncpy(tkn->data, line, 1);
	line += 1;
	*str = line;
	return (tkn);
}

t_tkn			*tkn_less(char **str)
{
	t_tkn	*tkn;
	char	*line;

	line = *str;
	if (*(line + 1) == '<')
	{
		if (*(line + 2) == '-')
			tkn = tkn_is_dlessdash(&line);
		else
			tkn = tkn_is_dless(&line);
	}
	else if (*(line + 1) == '&')
		tkn = tkn_is_lessand(&line);
	else
		tkn = tkn_is_less(&line);
	*str = line;
	return (tkn);
}
