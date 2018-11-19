/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ext_fun_type.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 23:50:39 by cormarti          #+#    #+#             */
/*   Updated: 2018/11/19 12:43:58 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXT_FUN_TYPE_H
# define EXT_FUN_TYPE_H

# include "lexer.h"

struct s_tkn_fun	g_tkn_fun[] =
{
	{'*', &tkn_asterisk},
	{' ', &tkn_wspace},
	{'\t', &tkn_htab},
//	{'\\', &tkn_escape},
	{'|', &tkn_pipe},
	{'&', &tkn_and},
	{'`', &tkn_bquote},
	//{'"', &tkn_word},
	//{'\'', &tkn_word},
	{';', &tkn_semi},
	{'!', &tkn_bang},
//	{'#', &tkn_hashtag},
	{'{', &tkn_lbrace},
	{'}', &tkn_rbrace},
	{'(', &tkn_lbracket},
	{')', &tkn_rbracket},
	{'>', &tkn_great},
	{'<', &tkn_less},
	{'\n', &tkn_newline},
	{0, 0},
};

#endif
