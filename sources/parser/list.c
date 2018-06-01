/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 04:31:24 by cormarti          #+#    #+#             */
/*   Updated: 2018/05/14 19:12:25 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/parser.h"

int		is_list(t_tkn **tkn)
{
	if (is_and_or(tkn))
	{
		if (is_separator_op(tkn))
		{
			if (is_list(tkn))
				return (1);
			else
				return (0);
		}
		return (1);
	}
	else
		return (0);
}
