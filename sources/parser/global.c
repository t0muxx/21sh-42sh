/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 18:26:11 by cormarti          #+#    #+#             */
/*   Updated: 2018/11/20 14:13:37 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "lexer.h"
#include "parser.h"
#include "astree.h"

static void		set_global_state(int chr)
{
	if (chr == '\'' && g_escape_state == 0)
		g_quote_state = g_quote_state == 0 ? 1 : 0;
	else if (chr == '\\' && g_escape_state == 0)
		g_escape_state = 1;
	else
		g_escape_state = 0;
}

static void		dup_value(char *src, char *dest, char *key, char *value)
{
	int		i;
	int		j;
	int		len;
	int		matched;

	i = 0;
	j = 0;
	matched = 0;
	len = (ft_strlen(src) - 1) + ft_strlen(value) - ft_strlen(key);
	while (j < len && src[i])
	{
		set_global_state(src[i]);
		if (g_escape_state == 0 && g_quote_state == 0 && src[i] == '$'
			&& matched == 0 && !ft_strncmp(src + (i + 1), key, ft_strlen(key)))
		{
			matched = 1;
			dest = global_concat(dest, value, i, len);
			i += (ft_strlen(key) + 1);
			j += ft_strlen(value);
		}
		else
			dest[j++] = src[i++];
	}
}

char			*global_replace(char *src, char *key, char *value)
{
	char	*dest;
	int		len;
	int		tmpa;
	int		tmpb;

	len = (ft_strlen(src) - 1) + ft_strlen(value) - ft_strlen(key);
	if (!(dest = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	dest[len] = '\0';
	tmpa = g_escape_state;
	tmpb = g_quote_state;
	g_escape_state = 0;
	g_quote_state = 0;
	dup_value(src, dest, key, value);
	g_escape_state = tmpa;
	g_quote_state = tmpb;
	free(src);
	return (dest);
}

static int		parse_globals(t_tkn *tkn, char **env)
{
	int		len;
	int		i;
	char	*initial_str;
	int		is_global;

	i = 0;
	is_global = 0;
	initial_str = ft_strdup(tkn->data);
	len = ft_strlen(initial_str);
	while (i < len)
		i = g_replace_var(&tkn, initial_str, i, env) + 1;
	i = 0;
	while (initial_str[i + 1])
	{
		if (initial_str[i] == '$' && ft_isalpha(initial_str[i + 1]))
			is_global = 1;
		i++;
	}
	if (initial_str != NULL)
		free(initial_str);
	return (is_global);
}

void			global_parsing(t_tkn **head, char ***env)
{
	t_tkn	*tkn;

	tkn = *head;
	if (parse_globals(tkn, *env) == 1)
	{
		if (ft_strcmp(tkn->data, "") == 0)
			tkn->type = CHR_EMPTY;
	}
	*head = tkn;
	g_quote_state = 0;
	g_quote_state = 0;
}
