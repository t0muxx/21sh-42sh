/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 11:00:31 by tmaraval          #+#    #+#             */
/*   Updated: 2018/05/17 22:15:45 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/parser.h"

enum e_tkn_type		type[][8] =
{
	{ CHR_IO_NUMBER, CHR_WORD, CHR_ASSIGNMENT_WORD, CHR_NULL },
	{ CHR_IO_NUMBER, CHR_WORD, CHR_ASSIGNMENT_WORD, CHR_NULL },
	{ CHR_IO_NUMBER, CHR_WORD, CHR_ASSIGNMENT_WORD, CHR_NULL },
	{ CHR_IO_NUMBER, CHR_WORD, CHR_ASSIGNMENT_WORD, CHR_NULL },
	{ CHR_IO_NUMBER, CHR_WORD, CHR_ASSIGNMENT_WORD, CHR_NULL },
	{ CHR_IO_NUMBER, CHR_WORD, CHR_ASSIGNMENT_WORD, CHR_NULL },
	{ CHR_IO_NUMBER, CHR_WORD, CHR_ASSIGNMENT_WORD, CHR_NULL },
	{ CHR_GREAT, CHR_CLOBBER, CHR_LESS, CHR_LESSAND, CHR_DGREAT, CHR_GREATAND,
CHR_LESSGREAT, CHR_NULL },
	{ CHR_WORD, CHR_NEWLINE, CHR_DASH, CHR_ASSIGNMENT_WORD, CHR_NULL },
	{ CHR_NULL },
	{ CHR_NULL },
	{ CHR_NULL },
	{ CHR_NULL },
	{ CHR_NULL },
	{ CHR_NULL },
	{ CHR_NULL },
	{ CHR_NULL },
	{ CHR_WORD, CHR_ASSIGNMENT_WORD, CHR_NEWLINE, CHR_NULL }, // SEMI
	{ CHR_NULL },
	{ CHR_WORD, CHR_ASSIGNMENT_WORD, CHR_NEWLINE, CHR_NULL },
	{ CHR_WORD, CHR_ASSIGNMENT_WORD, CHR_NEWLINE, CHR_NULL },
	{ CHR_IO_NUMBER, CHR_WORD, CHR_ASSIGNMENT_WORD, CHR_NEWLINE, CHR_NULL },
	{ CHR_IO_NUMBER, CHR_WORD, CHR_ASSIGNMENT_WORD, CHR_NEWLINE, CHR_NULL },
	{ CHR_IO_NUMBER, CHR_WORD, CHR_ASSIGNMENT_WORD, CHR_NEWLINE, CHR_NULL },
	{ CHR_IO_NUMBER, CHR_WORD, CHR_ASSIGNMENT_WORD, CHR_NEWLINE, CHR_NULL },
	{ CHR_IO_NUMBER, CHR_WORD, CHR_ASSIGNMENT_WORD, CHR_NEWLINE, CHR_NULL },
	{ CHR_IO_NUMBER, CHR_WORD, CHR_ASSIGNMENT_WORD, CHR_NEWLINE, CHR_NULL },
	{ CHR_IO_NUMBER, CHR_WORD, CHR_ASSIGNMENT_WORD, CHR_NEWLINE, CHR_NULL },
	{ CHR_IO_NUMBER, CHR_WORD, CHR_ASSIGNMENT_WORD, CHR_NEWLINE, CHR_NULL },
	{ CHR_IO_NUMBER, CHR_WORD, CHR_ASSIGNMENT_WORD, CHR_NEWLINE, CHR_NULL },
	{ CHR_IO_NUMBER, CHR_WORD, CHR_ASSIGNMENT_WORD, CHR_NEWLINE, CHR_NULL },
	{ CHR_IO_NUMBER, CHR_WORD, CHR_ASSIGNMENT_WORD, CHR_NEWLINE, CHR_NULL },
	{ CHR_IO_NUMBER, CHR_WORD, CHR_ASSIGNMENT_WORD, CHR_NEWLINE, CHR_NULL },
	{ CHR_IO_NUMBER, CHR_WORD, CHR_ASSIGNMENT_WORD, CHR_NEWLINE, CHR_NULL },
	{ CHR_IO_NUMBER, CHR_WORD, CHR_ASSIGNMENT_WORD, CHR_NEWLINE, CHR_NULL },
	{ CHR_IO_NUMBER, CHR_WORD, CHR_ASSIGNMENT_WORD, CHR_NEWLINE, CHR_NULL },
	{ CHR_IO_NUMBER, CHR_WORD, CHR_ASSIGNMENT_WORD, CHR_NEWLINE, CHR_NULL },
	{ CHR_IO_NUMBER, CHR_WORD, CHR_ASSIGNMENT_WORD, CHR_NEWLINE, CHR_NULL },
	{ CHR_IO_NUMBER, CHR_WORD, CHR_ASSIGNMENT_WORD, CHR_NEWLINE, CHR_NULL },
	{ CHR_IO_NUMBER, CHR_WORD, CHR_ASSIGNMENT_WORD, CHR_NEWLINE, CHR_NULL },
	{ CHR_IO_NUMBER, CHR_WORD, CHR_ASSIGNMENT_WORD, CHR_NEWLINE, CHR_NULL },
	{ CHR_IO_NUMBER, CHR_WORD, CHR_ASSIGNMENT_WORD, CHR_NEWLINE, CHR_NULL },
	{ CHR_IO_NUMBER, CHR_WORD, CHR_ASSIGNMENT_WORD, CHR_NEWLINE, CHR_NULL },
	{ CHR_IO_NUMBER, CHR_WORD, CHR_ASSIGNMENT_WORD, CHR_NEWLINE, CHR_NULL },
};

int		parse(t_tkn *tkn)
{
	int		i;

	i = 0;
	tkn = tkn->next;
	while (tkn->next)
	{
		ft_putendl(tkn->data);
		if (tkn->type == CHR_WORD || tkn->type == CHR_ASSIGNMENT_WORD)
			tkn = tkn->next;
		else
		{
		while (type[tkn->type][i] != CHR_NULL)
		{
			if (tkn->next->type == type[tkn->type][i])
			{
				i = 0;
				break ;
			}
			else
				i++;
		}
		if (type[tkn->type][i] == CHR_NULL)
		{
			ft_putstr("Syntax error : unexpected token ");
			ft_putendl(tkn->next->data);
			return (0);
		}
		else
			tkn = tkn->next;
		}
	}
	return (1);
}
/*
 ** complete_command : list separator
 **					 | list
 **					 ;
 **	list			 : list separator_op and_or
 **					 |					 and_or
 **					 ;
 ** and_or			 : pipeline
 **					 ;
 ** pipeline		 : pipe_sequence
 **					 | Bang pipe_sequence
 **					 ;
 ** pipe_sequence	 : command
 ** 				 | pipe_sequence '|' linebreak command
 ** 				 ;
 **	command			 : simple_command
 **					 ;
 ** simple_command	 : cmd_prefix cmd_word cmd_suffix
 **                  | cmd_prefix cmd_word
 **                  | cmd_prefix
 **                  | cmd_name cmd_suffix
 **                  | cmd_name
 ** 				 ;
 ** cmd_name         : WORD                   * Apply rule 7a *
 **                  ;
 ** cmd_word         : WORD                   * Apply rule 7b *
 **                  ;
 ** cmd_prefix       : io_redirect
 **                  | cmd_prefix io_redirect
 **				     | ASSIGNMENT_WORD
 **					 | cmd_prefix ASSIGNMENT_WORD
 **					 ;
 ** cmd_suffix       : io_redirect
 **                  | cmd_suffix io_redirect
 **				     | WORD
 **					 | cmd_suffix WORD
 **					 ;
 ** io_redirect      :           io_file
 **                  | IO_NUMBER io_file
 **	                 |           io_here
 **	                 | IO_NUMBER io_here
 **	                 ;
 ** io_file          : '<'       filename
 **                  | LESSAND   filename
 **	                 | '>'       filename
 **	                 | GREATAND  filename
 **	                 | DGREAT    filename
 **	                 | LESSGREAT filename
 **	                 | CLOBBER   filename
 **                  ;
 ** filename         : WORD                      * Apply rule 2 *
 **                  ;
 ** io_here          : DLESS     here_end
 **                  | DLESSDASH here_end
 **                  ;
 ** here_end         : WORD                      * Apply rule 3 *
 **                  ;
 ** separator_op     : ';'
 **                  ;
 ** separator        : separator_op
 **				     ;
 ** sequential_sep   : ';'
 **                  ;
 **
 */
