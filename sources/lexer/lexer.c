/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 10:43:25 by tmaraval          #+#    #+#             */
/*   Updated: 2018/03/22 15:54:37 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"
#include "error.h"

void	lexer_print_token(t_token *token)
{
	while (token)
	{
		ft_printf("data -> |%s| type -> |%c|\n", token->data, token->type);
		token = token->next;
	}
}

void	lexer_token_init(t_token **tok, int size)
{
	if(!((*tok)->data = (char *)malloc(sizeof(char) * (size + 1))))
		error_malloc_err();
	ft_bzero((*tok)->data, size + 1);
	(*tok)->type = C_INIT;
	(*tok)->next = NULL;
}

t_token *lexer_token_create(int size)
{
	t_token *new;

	if (!(new = (t_token *)malloc(sizeof(t_token))))
			error_malloc_err();
	lexer_token_init(&new, size);
	return (new);
}

int lexer_do(t_token *root_tok, char *line)
{
	int l_line;
	int	i;
	int state;
	int j;

	j = 0;
	t_token *tok;
	state = STATE_NORMAL;
	i = 0;
	l_line = (int)ft_strlen(line);
	tok = lexer_token_create(l_line);
	root_tok = tok;
	if (line == 0)
		return (0);
	if (line == NULL)
		return (-1);

	while (line[i] != '\0')
	{
		if (state == STATE_NORMAL)
		{
			if (line[i] == C_SEMILICON)
			{
				tok->data[j] = line[i++];
				tok->type = C_SEMILICON;
				tok->next = lexer_token_create(l_line - i);
				tok = tok->next;
				j = 0;
			}
			else if (line[i] == C_PIPE)
			{
				tok->data[j] = line[i++];
				tok->type = C_PIPE;
				tok->next = lexer_token_create(l_line - i);
				tok = tok->next;
				j = 0;
			}
			else if (line[i] == C_ISLESS)
			{
				tok->data[j] = line[i++];
				tok->type = C_ISLESS;
				tok->next = lexer_token_create(l_line - i);
				tok = tok->next;
				j = 0;
			}
			else if (line[i] == C_ISGREATER)
			{
				tok->data[j] = line[i++];
				tok->type = C_ISGREATER;
				tok->next = lexer_token_create(l_line - i);
				tok = tok->next;
				j = 0;
			}
			else if (line[i] == C_SIMPLEQUOTE)
			{
				tok->data[j++] = line[i++];
				tok->type = C_SIMPLEQUOTE;
				state = STATE_IN_QUOTE;
			}
			else if (line[i] == C_DOUBLEQUOTE)
			{
				tok->data[j++] = line[i++];
				tok->type = C_DOUBLEQUOTE;
				state = STATE_IN_DQUOTE;
			}
			else if (line[i] == C_WHITESPACE)
			{
				tok->data[j] = line[i++];
				tok->type = C_WHITESPACE;
				tok->next = lexer_token_create(l_line - i);
				tok = tok->next;
				j = 0;
			}
			else if (line[i] == C_AMPERSAND)
			{
				tok->data[j] = line[i++];
				tok->type = C_AMPERSAND;
				tok->next = lexer_token_create(l_line - i);
				tok = tok->next;
				j = 0;
			}
			else if (line[i] == C_ESCAPESEQ)
			{
				tok->data[j] = line[++i];
				tok->type = C_WORD;
				tok->next = lexer_token_create(l_line - i);
				tok = tok->next;
				j = 0;
			}
			else
			{
				tok->data[j++] = line[i++];
			   	tok->type = C_WORD;	
			}
		}
		if (state == STATE_IN_QUOTE)
		{
			tok->data[j++] = line[i++];
			if (line[i] == C_SIMPLEQUOTE)
			{
				state = STATE_NORMAL;
				tok->next = lexer_token_create(l_line - i);
				tok = tok->next;
				j = 0;
			}
		}
		if (state == STATE_IN_DQUOTE)
		{
			tok->data[j++] = line[i++];
			if (line[i] == C_DOUBLEQUOTE)
			{
				state = STATE_NORMAL;
				tok->next = lexer_token_create(l_line - i);
				tok = tok->next;
				j = 0;
			}
		}
	}
	return (1);
}
