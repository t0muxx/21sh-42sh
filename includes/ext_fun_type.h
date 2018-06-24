/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ext_fun_type.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 23:50:39 by cormarti          #+#    #+#             */
/*   Updated: 2018/06/24 18:31:02 by tomlulu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXT_FUN_TYPE_H
# define EXT_FUN_TYPE_H

# include "lexer.h"

struct s_tkn_fun	tkn_fun[] =
{
	{'*', &tkn_asterisk},
	{'$', &tkn_dollar},
	{'\t', &tkn_htab},
	{'\\', &tkn_escape},
	{'|', &tkn_pipe},
	{'&', &tkn_and},
	{'`', &tkn_bquote},
	{'"', &tkn_dquote},
	{'\'', &tkn_quote},
	{';', &tkn_semi},
	{'!', &tkn_bang},
	{'#', &tkn_hashtag},
	{'{', &tkn_lbrace},
	{'}', &tkn_rbrace},
	{'(', &tkn_lbracket},
	{')', &tkn_rbracket},
	{'>', &tkn_great},
	{'<', &tkn_less},
	{' ', &tkn_wspace},
	{'\n', &tkn_newline},
};

#endif
