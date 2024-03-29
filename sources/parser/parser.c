/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 11:00:31 by tmaraval          #+#    #+#             */
/*   Updated: 2018/10/15 11:11:27 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"

enum e_tkn_type		type[][8] =
{
	{ CHR_WORD, CHR_NULL },
	{ CHR_IO_NUMBER, CHR_WORD, CHR_NULL },
	{ CHR_IO_NUMBER, CHR_WORD, CHR_NULL },
	{ CHR_IO_NUMBER, CHR_WORD, CHR_DASH, CHR_NULL },
	{ CHR_IO_NUMBER, CHR_WORD, CHR_NULL },
	{ CHR_IO_NUMBER, CHR_WORD, CHR_DASH, CHR_NULL },
	{ CHR_IO_NUMBER, CHR_WORD, CHR_NULL },
	{ CHR_GREAT, CHR_CLOBBER, CHR_LESS, CHR_LESSAND, CHR_DGREAT, CHR_GREATAND,
		CHR_LESSGREAT, CHR_NULL },
	{ CHR_WORD, CHR_NEWLINE, CHR_DASH, CHR_ASSIGNMENT_WORD, CHR_NULL },
	{ CHR_IO_NUMBER, CHR_WORD, CHR_NULL },
	{ CHR_NULL },
	{ CHR_NULL },
	{ CHR_NULL },
	{ CHR_NULL },
	{ CHR_NULL },
	{ CHR_NULL },
	{ CHR_NULL },
	{ CHR_WORD, CHR_ASSIGNMENT_WORD, CHR_NEWLINE, CHR_NULL },
	{ CHR_NULL },
	{ CHR_EMPTY, CHR_WORD, CHR_ASSIGNMENT_WORD, CHR_EMPTY, CHR_NULL },
	{ CHR_WORD, CHR_ASSIGNMENT_WORD, CHR_NULL },
	{ CHR_WORD, CHR_ASSIGNMENT_WORD, CHR_NULL },
	{ CHR_NULL },
	{ CHR_NULL },
	{ CHR_NULL },
	{ CHR_NULL },
	{ CHR_GREAT, CHR_NULL },
	{ CHR_NULL },
	{ CHR_NULL },
	{ CHR_NULL },
	{ CHR_NULL },
	{ CHR_NULL },
	{ CHR_NULL },
	{ CHR_NULL },
	{ CHR_WORD, CHR_NULL },
	{ CHR_WORD, CHR_NULL },
	{ CHR_NULL },
};

static int			valid_tkn_type(t_tkn *tkn)
{
	int		i;

	i = 0;
	if (tkn->type == CHR_EMPTY || tkn->next->type == CHR_EMPTY)
		return (1);
	while (type[tkn->type][i] != CHR_NULL)
	{
		if (tkn->next->type == type[tkn->type][i])
			return (1);
		else
			i++;
	}
	return (0);
}

static int			parse_quote(t_tkn *tkn)
{
	int		parse_err;

	parse_err = 0;
	if (!tkn->next || tkn->next->type != CHR_WORD
		|| !tkn->next->next || tkn->next->next->type != CHR_QUOTE)
	{
		parse_err = 1;
		ft_putendl_fd("syntax error near unexpected token newline", 2);
	}
	return (parse_err);
}

static int			parse_dquote(t_tkn *tkn)
{
	int		parse_err;

	parse_err = 0;
	if (!tkn->next || tkn->next->type != CHR_WORD
		|| !tkn->next->next || tkn->next->next->type != CHR_DQUOTE)
	{
		parse_err = 1;
		ft_putendl_fd("syntax error near unexpected token newline", 2);
	}
	return (parse_err);
}

static int			parse_idle(t_tkn *tkn)
{
	int		parse_err;

	parse_err = 0;
	if (!valid_tkn_type(tkn))
	{
		parse_err = 1;
		ft_putstr_fd("syntax error near unexpected token ", 2);
		if (ft_strcmp(tkn->next->data, "\n") == 0)
			ft_putendl_fd("newline", 2);
		else
			ft_putendl_fd(tkn->next->data, 2);
	}
	return (parse_err);
}

int					parse(t_tkn *tkn)
{
	int		parse_err;

	parse_err = 0;
	while (tkn->next)
	{
		if (tkn->type == CHR_DQUOTE)
		{
			if ((parse_err = parse_dquote(tkn)) != 1)
				tkn = tkn->next->next;
		}
		else if (tkn->type == CHR_QUOTE)
		{
			if ((parse_err = parse_quote(tkn)) != 1)
				tkn = tkn->next->next;
		}
		else if (tkn->type != CHR_WORD
				&& tkn->type != CHR_ASSIGNMENT_WORD)
			parse_err = parse_idle(tkn);
		if (parse_err)
			return (0);
		else
			tkn = tkn->next;
	}
	return (1);
}
