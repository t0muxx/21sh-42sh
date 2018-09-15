/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 23:49:09 by cormarti          #+#    #+#             */
/*   Updated: 2018/09/15 18:04:25 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include <unistd.h>

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

/*static void		state_quoted(t_tkn **head, char **str, t_tkn_state *state)
{
	char		*line;
	int			len;
	t_tkn		*tkn;

	line = *str;
	len = 0;
	while (line[len] != '\0' && line[len] != '\'')
		len++;
	tkn = tkn_init(len);
	tkn->data = ft_strncpy(tkn->data, line, len);
	tkn->type = CHR_WORD;
	tkn_push_back(head, tkn);
	line += len;
	if (*line == '\'')
		tkn_push_back(head, tkn_quote(&line));
	*state = STATE_IDLE;
	*str = line;
}

static void		state_dquoted(t_tkn **head, char **str, t_tkn_state *state)
{
	char		*line;
	int			len;
	t_tkn		*tkn;

	line = *str;
	len = 0;
	while (line[len] != '\0' && line[len] != '"')
		len++;
	tkn = tkn_init(len);
	tkn->data = ft_strncpy(tkn->data, line, len);
	tkn->type = CHR_WORD;
	tkn_push_back(head, tkn);
	line += len;
	if (*line == '"')
		tkn_push_back(head, tkn_dquote(&line));
	*state = STATE_IDLE;
	*str = line;
}*/

t_tkn			*lex(char **str)
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
	return (tkn);
}
