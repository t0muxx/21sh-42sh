/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 02:05:19 by cormarti          #+#    #+#             */
/*   Updated: 2018/11/20 15:09:03 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"

# ifdef __linux__
#  define HOME_ROOT "/root"
#  define HOME_DIR  "/home/"
# else
#  define HOME_DIR  "/Users/"
# endif

enum			e_tkn_type
{
	CHR_GREAT,
	CHR_CLOBBER,
	CHR_LESS,
	CHR_LESSAND,
	CHR_DGREAT,
	CHR_GREATAND,
	CHR_LESSGREAT,
	CHR_IO_NUMBER,
	CHR_DASH,
	CHR_DLESS,
	CHR_DLESSDASH,
	CHR_LBRACKET,
	CHR_RBRACKET,
	CHR_LBRACE,
	CHR_RBRACE,
	CHR_HASHTAG,
	CHR_BANG,
	CHR_SEMI,
	CHR_DSEMI,
	CHR_PIPE,
	CHR_OR_IF,
	CHR_AND_IF,
	CHR_QUOTE,
	CHR_DQUOTE,
	CHR_WSPACE,
	CHR_BQUOTE,
	CHR_AND,
	CHR_ESCAPE,
	CHR_NEWLINE,
	CHR_WORD,
	CHR_DOLLAR,
	CHR_HTAB,
	CHR_ASTERISK,
	CHR_ASSIGNMENT_WORD,
	CHR_ANDGREAT,
	CHR_ANDDGREAT,
	CHR_EMPTY,
	CHR_TILDE,
	CHR_NULL,
};

enum			e_tkn_state
{
	STATE_BRACKETED = 1,
	STATE_QUOTED,
	STATE_DQUOTED,
	STATE_ESCAPED,
	STATE_HOOKED,
	STATE_IDLE,
};

typedef enum e_tkn_type		t_tkn_type;
typedef enum e_tkn_state	t_tkn_state;
typedef struct s_tkn		t_tkn;
typedef struct s_fun_tkn	t_fun_tkn;
typedef t_tkn *(*t_type_fun)(char**);

struct			s_tkn
{
	char		*data;
	t_tkn_type	type;
	t_tkn		*next;
	t_tkn		*prev;
};

struct			s_tkn_fun
{
	t_tkn_type		type;
	t_type_fun		fun;
};

extern struct s_tkn_fun		g_tkn_fun[];

t_tkn			*tkn_dollar(char **str);
t_tkn			*tkn_htab(char **str);
t_tkn			*tkn_asterisk(char **str);
t_tkn			*tkn_pipe(char **str);
t_tkn			*tkn_bquote(char **str);
t_tkn			*tkn_dquote(char **str);
t_tkn			*tkn_quote(char **str);
t_tkn			*tkn_and(char **str);
t_tkn			*tkn_semi(char **str);
t_tkn			*tkn_bang(char **str);
t_tkn			*tkn_hashtag(char **str);
t_tkn			*tkn_rbrace(char **str);
t_tkn			*tkn_lbrace(char **str);
t_tkn			*tkn_rbracket(char **str);
t_tkn			*tkn_lbracket(char **str);
t_tkn			*tkn_wspace(char **str);
t_tkn			*tkn_less(char **str);
t_tkn			*tkn_great(char **str);
t_tkn			*tkn_eol(char **str);
t_tkn			*tkn_word(char **str, char ***env);
t_tkn_state		set_state(t_tkn_state state, int chr, int is_esc);
int				is_tilde_type(char *str);
void			tilde_exp_browse_tkn(t_tkn *tkn, char ***env);
int				tkn_strlen(char *line);
int				is_quote(int chr, t_tkn_state state);
int				esc_strlen(char *line);
void			esc_push_pointer(char **str);
int				is_word_type(int c, int escaped, t_tkn_state state);
void			tkn_push_back(t_tkn **head, t_tkn *new);
t_tkn			*tkn_init(int len);
t_tkn			*lex(char **str, char ***env);
t_tkn			*tkn_newline(char **str);
t_tkn			*tkn_init_nl(void);
t_tkn			*tkn_dash(char **str);
t_tkn			*tkn_and(char **str);

#endif
