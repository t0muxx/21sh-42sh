/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 04:57:16 by cormarti          #+#    #+#             */
/*   Updated: 2018/06/01 01:34:06 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/parser.h"

int		is_simple_cmd(t_tkn **tkn)
{
	if (is_cmd_prefix(tkn))
		if (is_cmd_word(tkn))
			return (is_cmd_suffix(tkn) ? 1 : 1);
		else
			return (1);
	else if (is_cmd_name(tkn))
		return (is_cmd_suffix(tkn) ? 1 : 1);
	else
		return (0);
}

int		is_command(t_tkn **tkn)
{
	if (is_simple_cmd(tkn))
		return (1);
	else
		return (0);
}
