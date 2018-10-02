/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 23:49:09 by cormarti          #+#    #+#             */
/*   Updated: 2018/10/02 14:38:49 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "lexer.h"
#include <unistd.h>

static char		*str_concat(char *dest, char *value, int index, int len)
{
	int	i;
	int	val_len;

	i = 0;
	val_len = ft_strlen(value);
	while (index < len && i < val_len)
	{	
		dest[index] = value[i];
		index++;
		i++;
	}
	return (dest);
}

static char		*global_replace(char *src, char *key, char *value)
{
	char	*dest;
	int	len;
	int	i;
	int	j;
	int	replaced;

	i = 0;
	j = 0;
	replaced = 0;
	len = (ft_strlen(src) - 1) + ft_strlen(value) - ft_strlen(key);
	if (!(dest = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	dest[len] = '\0';
	while (j < len && src[i])
	{
		if (src[i] == '$' && !replaced)
		{
			dest = str_concat(dest, value, i, len);
			i += (ft_strlen(key) + 1);
			j += ft_strlen(value);
			replaced = 1;
		}
		else
			dest[j++] = src[i++];

		
	}
	free(src);
	return (dest);

}

static int		global_strlen(char *str, int index)
{
	int	len;

	len = 0;
	index++;
	if (!ft_isalpha(str[index]))
		return (0);
	while (str[index] != '\0' && ft_isalnum(str[index]) != 0)
	{
		len++;
		index++;
	}
	return (len);
}

static int		parse_globals(t_tkn *tkn, char **env)
{
	char	*key;
	char	*value;
	int	len;
	int	i;
	char	*initial_str;

	i = 0;
	len = 0;
	initial_str = ft_strdup(tkn->data);
	while (i < (int)ft_strlen(initial_str))
	{
		value = NULL;
		if (initial_str[i] == '$')
		{
			len = global_strlen(initial_str, i);
			if (!(key = (char*)malloc(sizeof(char) * (len + 1))))
				return (0);
			key[len] = '\0';
			key = ft_strncpy(key, initial_str + (i + 1), len);
			value = get_global_value(key, env);
			tkn->data = global_replace(tkn->data, key, value);
			free(key);
			i += len > 0 ? (len - 1) : 0;
		}
		i++;
	}
	if (initial_str != NULL)
		free(initial_str);
	return (ft_strchr(initial_str, '$') == 0 ? 0 : 1);

}



static void		state_idle(t_tkn **head, char **str, t_tkn_state *state)
{
	int			i;
	char		*line;

	line = *str;
	i = 0;
	(void)state;
	while (tkn_fun[i].type)
	{
		if (!tkn_fun[i + 1].type)
		{
			tkn_push_back(head, tkn_word(&line));
			break ;
		}
		else if (tkn_fun[i].type == (enum e_tkn_type)*line)
		{
			/*if (*line == '"')
				*state = STATE_DQUOTED;
			else if (*line == '\'')
				*state = STATE_QUOTED;
			*/tkn_push_back(head, tkn_fun[i].fun(&line));
			break ;
		}
		i++;
	}
	*str = line;
}

t_tkn			*lex(char **str, char ***env)
{
	t_tkn		*tkn;
	char		*line;
	t_tkn_state	state;
	t_tkn		*tmp;

	line = *str;
	tkn = tkn_init(1);
	state = STATE_IDLE;
	if (line == 0 || line == NULL)
		return (NULL);
	while (line[0] != '\0')
		state_idle(&tkn, &line, &state);
	tkn_push_back(&tkn, tkn_init_nl());
	tkn = tkn->next;
	free(tkn->prev->data);
	free(tkn->prev);
	tkn->prev = NULL;
	while (tkn->next)
	{
		if (parse_globals(tkn, *env) == 1)
		{
			if (ft_strcmp(tkn->data , "") == 0)
			{
			tmp = tkn;
			tkn = tkn->next;
			tkn->prev = tmp->prev ? tmp->prev : NULL;
			if (tmp->prev)
				(tkn->prev)->next = tkn;
			if (tmp->data)
				free(tmp->data);
			free(tmp);
			}
			else
			{
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
			}
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
	return (tkn);
}
