/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 23:49:09 by cormarti          #+#    #+#             */
/*   Updated: 2018/11/22 09:54:25 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "global.h"
#include "exec.h"
#include "memory.h"
#include <unistd.h>

int				g_replace_default(t_tkn *tkn, char *str, int index, char **env)
{
	int		len;
	char	*key;
	char	*value;

	key = NULL;
	value = NULL;
	len = global_strlen(str, index);
	if (!(key = (char*)malloc(sizeof(char) * (len + 1))))
		return (0);
	key[len] = '\0';
	key = ft_strncpy(key, str + (index + 1), len);
	value = get_global_value(key, env);
	tkn->data = global_replace(tkn->data, key, value);
	if (key)
		free(key);
	if (value != NULL)
		free(value);
	return (len == 0 ? 0 : len - 1);
}

int				g_replace_pid(t_tkn *tkn)
{
	char	key[2];
	char	*value;

	key[0] = '$';
	key[1] = '\0';
	value = ft_itoa((int)getpid());
	tkn->data = global_replace(tkn->data, key, value);
	if (value)
		free(value);
	return (1);
}

int				g_replace_var(t_tkn **head, char *str, int index, char **env)
{
	t_tkn	*tkn;

	tkn = *head;
	if (str[index] == '\'' && g_escape_state == 0)
		g_quote_state = g_quote_state == 0 ? 1 : 0;
	else if (str[index] == '\\' && g_escape_state == 0 && g_quote_state == 0)
		g_escape_state = 1;
	else if (g_escape_state == 0 && g_quote_state == 0)
	{
		if (str[index] == '$' && str[index + 1] && ft_isalpha(str[index + 1]))
			index += g_replace_default(tkn, str, index, env);
		else if (str[index] == '$' && str[index + 1] && str[index + 1] == '$')
			index += g_replace_pid(tkn);
	}
	else
		g_escape_state = 0;
	*head = tkn;
	return (index);
}

static void		state_idle(t_tkn **head, char **str,
					t_tkn_state *state, char ***env)
{
	int		i;
	char	*line;

	line = *str;
	i = 0;
	(void)state;
	while (g_tkn_fun[i].type)
	{
		if (!g_tkn_fun[i + 1].type)
		{
			tkn_push_back(head, tkn_word(&line, env));
			break ;
		}
		else if (g_tkn_fun[i].type == (enum e_tkn_type)*line)
		{
			tkn_push_back(head, g_tkn_fun[i].fun(&line));
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

	line = *str;
	tkn = tkn_init(1);
	state = STATE_IDLE;
	if (line == 0 || line == NULL)
		return (NULL);
	while (line[0] != '\0')
	{
		state_idle(&tkn, &line, &state, env);
		while (tkn->next)
			tkn = tkn->next;
		if (tkn->type == CHR_ASSIGNMENT_WORD
			&& (tkn->prev->type == CHR_NULL || tkn->prev->type == CHR_SEMI))
			insert_global(tkn->data, env, 0);
		while (tkn->prev)
			tkn = tkn->prev;
	}
	tkn_push_back(&tkn, tkn_init_nl());
	delete_first_item(&tkn);
	tilde_exp_browse_tkn(tkn, env);
	return (tkn);
}
