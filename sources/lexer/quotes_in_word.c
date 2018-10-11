/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_in_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 10:34:58 by cormarti          #+#    #+#             */
/*   Updated: 2018/10/11 11:52:41 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int				is_quote(int chr, t_tkn_state state)
{
	if (chr == '"')
		return (state == STATE_QUOTED ? 0 : 1);
	else if (chr == '\'')
		return (state == STATE_DQUOTED ? 0 : 1);
	else
		return (0);
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
		if (line[i] == '\\' && state == STATE_IDLE)
			is_esc = 1;
		else
			is_esc = 0;
		i++;
	}
	line += i;
	*str = line;
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
		if (line[i] == '\\' && state == STATE_IDLE)
			is_esc = 1;
		else
		{
			if (is_esc && (line[i] == '\'' || line[i] == '"'))
				len++;
			is_esc = 0;
		}
		len = (!is_esc && !is_quote(line[i], state)) ? len + 1 : len;
		i++;
	}
	return (len);
}
