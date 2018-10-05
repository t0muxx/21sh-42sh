/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 23:49:09 by cormarti          #+#    #+#             */
/*   Updated: 2018/10/05 15:13:19 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "global.h"
#include "lexer.h"
#include <unistd.h>

int				replace_var(t_tkn **head, char *str, int index, char **env)
{
	char	*key;
	char	*value;
	int		len;
	t_tkn	*tkn;

	len = 0;
	key = NULL;
	value = NULL;
	tkn = *head;
	if (str[index] == '$' && str[index + 1] && ft_isalpha(str[index + 1]))
	{
		len = global_strlen(str, index);
		if (!(key = (char*)malloc(sizeof(char) * (len + 1))))
			return (0);
		key[len] = '\0';
		key = ft_strncpy(key, str + (index + 1), len);
		value = get_global_value(key, env);
		tkn->data = global_replace(tkn->data, key, value);
		free(key);
		free(value);
		index += len > 0 ? (len) : 0;
	}
	*head = tkn;
	return (str[index] ? index : index - 1);
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
			tkn_push_back(head, tkn_fun[i].fun(&line));
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
		state_idle(&tkn, &line, &state);
	tkn_push_back(&tkn, tkn_init_nl());
	tkn = tkn->next;
	free(tkn->prev->data);
	free(tkn->prev);
	tkn->prev = NULL;
	global_parsing(&tkn, env);
	return (tkn);
}
