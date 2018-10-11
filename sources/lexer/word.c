/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 05:15:34 by cormarti          #+#    #+#             */
/*   Updated: 2018/10/11 11:39:01 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

char				*esc_strncpy(char *dst, char **line, int len)
{
	t_tkn_state		state;
	int				i;
	int				j;
	int				is_esc;
	char			*src;

	src = *line;
	i = 0;
	j = 0;
	is_esc = 0;
	state = STATE_IDLE;
	while (j < len && src[i] != '\0')
	{
		state = set_state(state, src[i], is_esc);
		if (src[i] == '\\' && state == STATE_IDLE)
			is_esc = 1;
		else
		{
			if (is_esc && (src[i] == '\'' || src[i] == '"'))
				dst[j++] = src[i];
			is_esc = 0;
		}
		if (!is_esc && !is_quote(src[i], state))
			dst[j++] = src[i];
		i++;
	}
	dst[len] = '\0';
	src += (state == STATE_IDLE) ? i : i + 1;
	*line = src;
	return (dst);
}

int					is_word_type(int c, int escaped, t_tkn_state state)
{
	int		i;

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

int					strdigit(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static t_tkn_type	extra_tkn_type(t_tkn *tkn, char **str)
{
	if (*str[0] == '>' && strdigit(tkn->data))
		return (CHR_IO_NUMBER);
	else if (ft_strchr(tkn->data, '='))
	{
//		ft_printf("assign = %s\n", tkn->data);
		return (CHR_ASSIGNMENT_WORD);
	}
	else
		return (CHR_WORD);
}

t_tkn				*tkn_word(char **str)
{
	t_tkn	*tkn;
	int		len;
	char	*line;

	line = *str;
	len = esc_strlen(line);
	tkn = tkn_init(len);
	if (len > 0)
	{
		tkn->data = esc_strncpy(tkn->data, &line, len);	
		*str = line;
		tkn->type = extra_tkn_type(tkn, str);
	}
	else
	{
		tkn->type = CHR_WORD;
		esc_push_pointer(&line);
		*str = line;
	}
	return (tkn);
}
