/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 10:43:50 by tmaraval          #+#    #+#             */
/*   Updated: 2018/03/22 15:55:02 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

enum e_token_type
{
	C_SEMILICON = ';',
	C_PIPE = '|',
	C_ISLESS = '<',
	C_ISGREATER = '>',
	C_NUMBER,
	C_WORD,
	C_SIMPLEQUOTE = '\'',
	C_DOUBLEQUOTE = '\"',
	C_WHITESPACE = ' ',
	C_AMPERSAND = '&',
	C_ESCAPESEQ = '\\',
	C_INIT = -1,
};

enum e_state_type
{
	STATE_IN_QUOTE,
	STATE_IN_DQUOTE,
	STATE_NORMAL,

};

typedef struct 	s_token
{
	char			*data;
	int				type;
	struct s_token 	*next;

}				t_token;

void	lexer_print_token(t_token *token)
void	lexer_token_init(t_token **tok, int size)
t_token *lexer_token_create(int size)
int lexer_do(t_token *root_tok, char *line)
#endif
