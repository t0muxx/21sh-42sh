/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 04:09:27 by cormarti          #+#    #+#             */
/*   Updated: 2018/05/15 16:08:28 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/parser.h"

int		is_complete_cmd(t_tkn *tkn)
{
	ft_putendl("------- START PARSING ------");
	if (is_list(&tkn))
	{
		return (is_separator(&tkn) ? 1 : 1);
	}
	else
		return (0);
}
