/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 05:15:34 by cormarti          #+#    #+#             */
/*   Updated: 2018/11/08 14:10:22 by tomux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "lexer.h"
#include "utils.h"

int					process_copy(char *src, char **dst_head,
					t_tkn_state *state, int len)
{
	int			i;
	int			j;
	char		*dst;

	i = 0;
	j = 0;
	dst = *dst_head;
	while (j < len && src[i] != '\0')
	{
		*state = set_state(*state, src[i], g_escape_state);
		if (g_escape_state == 0 && src[i] == '\\' && *state == STATE_IDLE)
			g_escape_state = 1;
		else if (g_escape_state == 1 && ((src[i] == '\'' || src[i] == '"') || (src[i] == '\\')))
		{
			dst[j++] = src[i];
			g_escape_state = 0;
		}
		else if (g_escape_state == 0 && !is_quote(src[i], *state))
			dst[j++] = src[i];
		i++;
	}
	dst[j] = '\0';
	return ((*dst_head = dst) ? i : i);
}

char				*esc_strncpy(char *dst, char *src, int len)
{
	t_tkn_state	state;
	int			ret;

	state = STATE_IDLE;
	ret = process_copy(src, &dst, &state, len);
	dst[len] = '\0';
	src += (state == STATE_IDLE) ? ret : ret + 1;
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

t_tkn				*tkn_word(char **str, char ***env)
{
	t_tkn	*tkn;
	int		len;
	char	*line;
	t_tkn	*tmp_tkn;
	int		firstlen;

	line = *str;
	firstlen = tkn_strlen(line);
	len = tkn_strlen(line);
	tmp_tkn = tkn_init(len);
	ft_strncpy(tmp_tkn->data, line, len);
	tmp_tkn->type = is_tilde_type(tmp_tkn->data) ? CHR_TILDE : extra_tkn_type(tmp_tkn, &(tmp_tkn->data));
	global_parsing(&tmp_tkn, env);
	len = esc_strlen(tmp_tkn->data);
	tkn = tkn_init(len);
	if (len > 0)
	{	
		tkn->data = esc_strncpy(tkn->data, tmp_tkn->data, len);
		*str = line + firstlen;
		tkn->type = tmp_tkn->type == CHR_TILDE ? CHR_TILDE : extra_tkn_type(tkn, str);
	}
	else
	{
		tkn->type = tkn->type ? tkn->type : CHR_WORD;
		esc_push_pointer(&line);
		*str = line;
	}
	return (tkn);
}
