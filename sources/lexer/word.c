/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 05:15:34 by cormarti          #+#    #+#             */
/*   Updated: 2018/11/07 15:37:24 by tomux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "utils.h"

int					process_copy(char *src, char **dst_head,
					t_tkn_state *state, int len)
{
	int			i;
	int			j;
	int			esc;
	char		*dst;

	i = 0;
	j = 0;
	esc = 0;
	dst = *dst_head;
	while (j < len && src[i] != '\0')
	{
		*state = set_state(*state, src[i], esc);
		if (!esc && src[i] == '\\' && *state == STATE_IDLE)
			esc = 1;
		else
		{
			if (esc && ((src[i] == '\'' || src[i] == '"') || (src[i] == '\\')))
				dst[j] = src[i];
			esc = 0;
		}
		if (!esc && !is_quote(src[i], *state))
			dst[j++] = src[i];
		i++;
	}
	return ((*dst_head = dst) ? i : i);
}

char				*esc_strncpy(char *dst, char **line, int len)
{
	t_tkn_state	state;
	char		*src;
	int			ret;

	src = *line;
	state = STATE_IDLE;
	ret = process_copy(src, &dst, &state, len);
	dst[len] = '\0';
	src += (state == STATE_IDLE) ? ret : ret + 1;
	*line = src;
	return (dst);
}

int					is_word_type(int c, int escaped, t_tkn_state state)
{
	int			i;

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

static t_tkn_type	extra_tkn_type(t_tkn *tkn, char **str)
{
	if (*str[0] == '>' && strdigit(tkn->data))
		return (CHR_IO_NUMBER);
	else if (ft_strchr(tkn->data, '='))
		return (CHR_ASSIGNMENT_WORD);
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
