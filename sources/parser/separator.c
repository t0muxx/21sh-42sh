/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 04:38:13 by cormarti          #+#    #+#             */
/*   Updated: 2018/06/01 01:35:53 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/parser.h"

int		is_newline_list(t_tkn **tkn)
{
	if (*tkn == NULL)
		return (0);
	return ((*tkn)->data[0] == '\0' ? 1 : 0);
}

int		is_separator_op(t_tkn **tkn)
{
	if (*tkn && ((*tkn)->type == CHR_AND || (*tkn)->type == CHR_SEMI))
	{
		ft_putstr("token = ");
		ft_putendl((*tkn)->data);
		*tkn = (*tkn)->next ? (*tkn)->next : *tkn;
		return (1);
	}
	else
		return (0);
}

int		is_separator(t_tkn **tkn)
{
	if (is_separator_op(tkn))
	{
		if (*tkn && (*tkn)->data[0] == '\0')
		{
			ft_putstr("token = ");
			ft_putendl((*tkn)->data);
			*tkn = (*tkn)->next ? (*tkn)->next : *tkn;
			return (1);
		}
		else
			return (0);
	}
	else if (is_newline_list(tkn))
		return (1);
	else
		return (0);
}
