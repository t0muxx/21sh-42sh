/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 18:26:11 by cormarti          #+#    #+#             */
/*   Updated: 2018/10/03 20:18:44 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "lexer.h"
#include "parser.h"
#include "astree.h"

static void		dup_value(char *src, char *dest, char *key, char *value)
{
	int		i;
	int		j;
	int		len;
	int		replaced;

	i = 0;
	j = 0;
	len = (ft_strlen(src) - 1) + ft_strlen(value) - ft_strlen(key);
	replaced = 0;
	while (j < len && src[i])
	{
		if (src[i] == '$' && !replaced)
		{
			dest = global_concat(dest, value, i, len);
			i += (ft_strlen(key) + 1);
			j += ft_strlen(value);
			replaced = 1;
		}
		else
			dest[j++] = src[i++];
	}
}

char		*global_replace(char *src, char *key, char *value)
{
	char	*dest;
	int		len;

	len = (ft_strlen(src) - 1) + ft_strlen(value) - ft_strlen(key);
	if (!(dest = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	dest[len] = '\0';
	dup_value(src, dest, key, value);
	free(src);
	return (dest);
}

static int		parse_globals(t_tkn *tkn, char **env)
{
	int		len;
	int		i;
	char	*initial_str;

	i = 0;
	initial_str = ft_strdup(tkn->data);
	len = ft_strlen(initial_str);
	while (i < len)
		i = replace_var(&tkn, initial_str, i, env) + 1;
	if (ft_strchr(initial_str, '$') == 0)
	{
		if (initial_str != NULL)
			free(initial_str);
		return (0);
	}
	if (initial_str != NULL)
		free(initial_str);
	return (1);
}

static void		link_tkn_lst(t_tkn **head, char ***env)
{
	t_tkn	*tkn;
	t_tkn	*tmp;

	tkn = *head;
	tmp = tkn;
	tkn = lex(&tkn->data, env);
	tkn->prev = tmp->prev;
	if (tkn->prev)
		(tkn->prev)->next = tkn;
	while (tkn->next->type != CHR_NEWLINE)
		tkn = tkn->next;
	free(tkn->next->data);
	free(tkn->next);
	tkn->next = tmp->next;
	(tkn->next)->prev = tkn;
	free(tmp->data);
	free(tmp);
	*head = tkn;
}

void			global_parsing(t_tkn **head, char ***env)
{
	t_tkn	*tmp;
	t_tkn	*tkn;

	tkn = *head;
	tmp = NULL;
	while (tkn->next)
	{
		if (parse_globals(tkn, *env) == 1)
		{
			if (ft_strcmp(tkn->data, "") == 0)
				tkn->type = CHR_EMPTY;
			else
				link_tkn_lst(&tkn, env);
		}
		else
		{
			if (tkn->type == CHR_ASSIGNMENT_WORD)
				insert_global(tkn->data, env);
			tkn = tkn->next;
		}
	}
	while (tkn->prev)
		tkn = tkn->prev;
	*head = tkn;
}
