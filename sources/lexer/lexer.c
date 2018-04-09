/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 23:49:09 by cormarti          #+#    #+#             */
/*   Updated: 2018/03/31 04:51:41 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/ext_fun_type.h"
#include <stdio.h>

t_tkn		*tkn_init(int len)
{
	t_tkn	*tkn;

	tkn = NULL;
	if (len == 0)
		return (NULL);
	if (!(tkn = (t_tkn*)malloc(sizeof(t_tkn)))
			|| !(tkn->data = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	tkn->data[len] = '\0';
	tkn->type = CHR_NULL;
	tkn->next = NULL;
	return (tkn);
}

static void	print_tkn_struct(t_tkn *tkn)
{
	tkn = tkn->next;
	while (tkn)
	{
		ft_putendl(tkn->data);
		tkn = tkn->next;
	}
}

static void	state_idle(t_tkn **head, char **str, t_tkn_state *state)
{
	int		i;
	char	*line;

	line = *str;
	i = 0;
	while (tkn_fun[i].type)
	{
		if (!tkn_fun[i + 1].type)
		{
			tkn_push_back(head, tkn_word(&line));
			break;
		}
		else if (tkn_fun[i].type == *line)
		{
			if (*line == CHR_DQUOTE)
				*state = STATE_DQUOTED;
			else if (*line == CHR_QUOTE)
				*state = STATE_QUOTED;
			tkn_push_back(head, tkn_fun[i].fun(&line));
			break;
		}
		i++;
	}
	*str = line;
}

static void	state_quoted(t_tkn **head, char **str, t_tkn_state *state)
{
	char	*line;
	int		len;
	t_tkn	*tkn;

	line = *str;
	len = 0;
	while (line[len] != '\0' && line[len] != CHR_QUOTE)
		len++;
	tkn = tkn_init(len);
	tkn->data = ft_strncpy(tkn->data, line, len);
	tkn->type = CHR_WORD;
	tkn_push_back(head, tkn);
	line += len;
	if (*line == CHR_QUOTE)
		tkn_push_back(head, tkn_quote(&line));
	*state = STATE_IDLE;
	*str = line;
}

static void	state_dquoted(t_tkn **head, char **str, t_tkn_state *state)
{
	char	*line;
	int		len;
	t_tkn	*tkn;

	line = *str;
	len = 0;
	while (line[len] != '\0' && line[len] != CHR_DQUOTE)
		len++;
	tkn = tkn_init(len);
	tkn->data = ft_strncpy(tkn->data, line, len);
	tkn->type = CHR_WORD;
	tkn_push_back(head, tkn);
	line += len;
	if (*line == CHR_DQUOTE)
		tkn_push_back(head, tkn_dquote(&line));
	*state = STATE_IDLE;
	*str = line;
}

static void	lex(char **str)
{
	int		i;
	t_tkn	*tkn;
	char	*line;
	t_tkn_state	state;

	line = ft_strdup(*str);
	tkn = tkn_init(1);
	state = STATE_IDLE;
	while (*line != '\0')
	{
		i = 0;
		if (state == STATE_IDLE)
			state_idle(&tkn, &line, &state);
		else if (state == STATE_DQUOTED)
			state_dquoted(&tkn, &line, &state);
		else if (state == STATE_QUOTED)
			state_quoted(&tkn, &line, &state);
	}
	print_tkn_struct(tkn);
}

int			main(int argc, char **argv)
{
	(void)argc;
	lex(&argv[1]);
	return (0);
}
