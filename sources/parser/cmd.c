/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 05:30:06 by cormarti          #+#    #+#             */
/*   Updated: 2018/06/01 01:34:45 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/parser.h"

int		is_cmd_name(t_tkn **tkn)
{
	if (*tkn && (*tkn)->type == CHR_WORD)
	{
		ft_putstr("NAME WORD token = ");
		ft_putendl((*tkn)->data);
		*tkn = (*tkn)->next;
		return (1);
	}
	else
		return (0);
}

int		is_cmd_word(t_tkn **tkn)
{
	if (*tkn && (*tkn)->type == CHR_WORD)
	{
		ft_putstr("WORD WORD token = ");
		ft_putendl((*tkn)->data);
		*tkn = (*tkn)->next;
		return (1);
	}
	else
		return (0);
}

int		is_cmd_suffix(t_tkn **tkn)
{
	if (is_io_redirect(tkn))
		return (1);
	else if ((*tkn)->type == CHR_WORD)
	{
		ft_putstr("SUFFIX WORD token = ");
		ft_putendl((*tkn)->data);
		*tkn = (*tkn)->next;
		return (1);
	}
	else if ((*tkn)->type == CHR_WORD)
	{
		*tkn = (*tkn)->next;
		return (0);
	}
	else
		return (0);
}

int		is_cmd_prefix(t_tkn **tkn)
{
	if (is_io_redirect(tkn))
		return (1);
	else if ((*tkn)->type == CHR_WORD)
	{
		while ((*tkn)->next)
		{
			ft_putstr("PREFIX WORD token = ");
			ft_putendl((*tkn)->data);
			*tkn = (*tkn)->next;
		}
		return (1);
	}
	else if ((*tkn)->type == CHR_WORD)
	{
		*tkn = (*tkn)->next;
		return (1);
	}
	else
		return (0);
}
