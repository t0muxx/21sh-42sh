/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 19:33:40 by cormarti          #+#    #+#             */
/*   Updated: 2018/03/31 04:25:44 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"

enum e_tkn_type
{
	CHR_LESS = '<',
	CHR_DLESS = 999,
	CHR_DLESSDASH = 998,
	CHR_GREAT = '>',
	CHR_DGREAT = 997,
	CHR_LBRACKET = '(',
	CHR_RBRACKET = ')',
	CHR_LBRACE = '{',
	CHR_RBRACE = '}',
	CHR_HASHTAG = '#',
	CHR_BANG = '!',
	CHR_LESSAND = 996,
	CHR_GREATAND = 995,
	CHR_SEMI = ';',
	CHR_DSEMI = 994,
	CHR_LESSGREAT = 993,
	CHR_CLOBBER = 992,
	CHR_OR_IF = 991,
	CHR_AND_IF = 990,
	CHR_PIPE = '|',
	CHR_QUOTE = '\'',
	CHR_DQUOTE = '"',
	CHR_WSPACE = ' ',
	CHR_BQUOTE = '`',
	CHR_AND = '&',
	CHR_DASH = '-',
	CHR_ESCAPE = '\\',
	CHR_EOL = '\n',
	CHR_DOLLAR = '$',
	CHR_HTAB = '\t',
	CHR_ASTERISK = '*',
	CHR_NULL = 0,
	CHR_WORD = 1,
};

enum e_tkn_state
{
	STATE_QUOTED,
	STATE_DQUOTED,
	STATE_BRACKETED,
	STATE_ESCAPED,
	STATE_HOOKED,
	STATE_IDLE,
};

typedef enum e_tkn_state	t_tkn_state;
typedef struct s_tkn		t_tkn;
typedef struct s_fun_tkn	t_fun_tkn;
typedef t_tkn *(*type_fun)(char**);

struct	s_tkn
{
	char		*data;
	enum e_tkn_type	type;
	t_tkn		*next;
};

struct	s_tkn_fun
{
	enum e_tkn_type	type;
	type_fun		fun;
};

extern struct s_tkn_fun		tkn_fun[];

t_tkn	*tkn_dollar(char **str);
t_tkn	*tkn_htab(char **str);
t_tkn	*tkn_asterisk(char **str);
t_tkn	*tkn_escape(char **str);
t_tkn	*tkn_dash(char **str);
t_tkn	*tkn_pipe(char **str);
t_tkn	*tkn_bquote(char **str);
t_tkn	*tkn_dquote(char **str);
t_tkn	*tkn_quote(char **str);
t_tkn	*tkn_and(char **str);
t_tkn	*tkn_semi(char **str);
t_tkn	*tkn_bang(char **str);
t_tkn	*tkn_hashtag(char **str);
t_tkn	*tkn_rbrace(char **str);
t_tkn	*tkn_lbrace(char **str);
t_tkn	*tkn_rbracket(char **str);
t_tkn	*tkn_lbracket(char **str);
t_tkn	*tkn_wspace(char **str);
t_tkn	*tkn_less(char **str);
t_tkn	*tkn_great(char **str);
t_tkn	*tkn_eol(char **str);
t_tkn	*tkn_word(char **str);
void	tkn_push_back(t_tkn **head, t_tkn *new);
t_tkn	*tkn_init(int len);

#endif
