/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 05:15:34 by cormarti          #+#    #+#             */
/*   Updated: 2018/09/04 14:33:33 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

static char			*esc_strncpy(char *dst, char *src, int len)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (j < len && src[i])
	{
		if ((src[i] != '\\') || (i != 0 && src[i - 1] == '\\'))
		{
			dst[j] = src[i];
			if ((dst[j] = src[i]) == 0)
			{
				while (i < len)
				{
					dst[j] = '\0';
					i++;
				}
			}
			j++;
		}
		i++;
	}
	return (dst);
}

static int			is_word_type(int c)
{
	int		i;

	i = 0;
	if (c == '\\')
		return (1);
	while (tkn_fun[i].type)
	{
		if (tkn_fun[i].type == (enum e_tkn_type)c)
			return (0);
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
		return (CHR_ASSIGNMENT_WORD);
	else
		return (CHR_WORD);
}

t_tkn				*tkn_word(char **str)
{
	t_tkn	*tkn;
	int		len;
	int		i;
	char	*line;
	int		is_esc;

	is_esc = 0;
	line = *str;
	len = 0;
	i = 0;
	while (line[i] != '\0' && is_word_type(line[i]))
	{
		if (line[i] == '\\' && !is_esc)
			is_esc = 1;
		else
			is_esc = (len++) ? 0 : 0;
		i++;
	}
	tkn = tkn_init(len);
	tkn->data = esc_strncpy(tkn->data, line, len);
	line += i;
	*str = line;
	tkn->type = extra_tkn_type(tkn, str);
	return (tkn);
}
