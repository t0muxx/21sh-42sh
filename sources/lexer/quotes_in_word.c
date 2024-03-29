/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_in_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 10:34:58 by cormarti          #+#    #+#             */
/*   Updated: 2018/11/20 15:07:24 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "lexer.h"

t_tkn_state		set_state(t_tkn_state state, int chr, int is_esc)
{
	t_tkn_state		new_state;

	new_state = state;
	if (is_esc)
		return (new_state);
	if (chr == '\'' && state != STATE_DQUOTED)
		new_state = (state == STATE_IDLE) ? STATE_QUOTED : STATE_IDLE;
	if (chr == '"' && state != STATE_QUOTED)
		new_state = (state == STATE_IDLE) ? STATE_DQUOTED : STATE_IDLE;
	return (new_state);
}

int				is_word_type(int c, int escaped, t_tkn_state state)
{
	int				i;

	i = 0;
	if (escaped || c == '\\' || state != STATE_IDLE)
		return (1);
	while (g_tkn_fun[i].type)
	{
		if (g_tkn_fun[i].type == (enum e_tkn_type)c)
		{
			if (c == '\'' || c == '"')
				return (1);
			return (0);
		}
		i++;
	}
	return (1);
}

void			esc_push_pointer(char **str)
{
	t_tkn_state		state;
	char			*line;
	int				is_esc;
	int				i;

	line = *str;
	i = 0;
	is_esc = 0;
	state = STATE_IDLE;
	while (line[i] != '\0' && is_word_type(line[i], is_esc, state))
	{
		state = set_state(state, line[i], is_esc);
		if (!is_esc && line[i] == '\\' && state == STATE_IDLE)
			is_esc = 1;
		else
			is_esc = 0;
		i++;
	}
	line += i;
	*str = line;
}

int				tkn_strlen(char *line)
{
	t_tkn_state		state;
	int				i;
	int				is_esc;

	i = 0;
	is_esc = 0;
	state = STATE_IDLE;
	while (line[i] != '\0' && is_word_type(line[i], is_esc, state))
	{
		state = set_state(state, line[i], is_esc);
		if (!is_esc && line[i] == '\\' && state == STATE_IDLE)
			is_esc = 1;
		else
			is_esc = 0;
		i++;
	}
	return (i);
}

int				esc_strlen(char *line)
{
	int				len;
	t_tkn_state		state;
	int				i;
	int				is_esc;

	len = 0;
	i = 0;
	is_esc = 0;
	state = STATE_IDLE;
	while (line[i] != '\0' && is_word_type(line[i], is_esc, state))
	{
		state = set_state(state, line[i], is_esc);
		if (!is_esc && line[i] == '\\' && state == STATE_IDLE)
			is_esc = 1;
		else
		{
			if (is_esc && ((line[i] == '\'' || line[i] == '"')
						|| line[i] == '\\'))
				len++;
			is_esc = 0;
		}
		len = (!is_esc && !is_quote(line[i], state)) ? len + 1 : len;
		i++;
	}
	return (len);
}
