/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ext_fun_type.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 23:50:39 by cormarti          #+#    #+#             */
/*   Updated: 2018/05/14 17:07:07 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXT_FUN_TKN_H
# define EXT_FUN_TKN_H

#include "lexer.h"

struct s_tkn_fun	tkn_fun[] =
{
	{CHR_ASTERISK, &tkn_asterisk},	
	{CHR_DOLLAR, &tkn_dollar},
	{CHR_HTAB, &tkn_htab},
	{CHR_DASH, &tkn_dash},
	{CHR_ESCAPE, &tkn_escape},
	{CHR_PIPE, &tkn_pipe},
	{CHR_AND, &tkn_and},
	{CHR_BQUOTE, &tkn_bquote},
	{CHR_DQUOTE, &tkn_dquote},
	{CHR_QUOTE, &tkn_quote},
	{CHR_SEMI, &tkn_semi},
	{CHR_BANG, &tkn_bang},
	{CHR_HASHTAG, &tkn_hashtag},
	{CHR_LBRACE, &tkn_lbrace},
	{CHR_RBRACE, &tkn_rbrace},
	{CHR_LBRACKET, &tkn_lbracket},
	{CHR_RBRACKET, &tkn_rbracket},
	{CHR_WSPACE, &tkn_wspace},
	{CHR_GREAT, &tkn_great},
	{CHR_LESS, &tkn_less},
	{CHR_WORD, &tkn_word},
//	{CHR_NEWLINE, &tkn_newline},
};

#endif
