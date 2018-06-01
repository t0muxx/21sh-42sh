/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 05:44:14 by cormarti          #+#    #+#             */
/*   Updated: 2018/05/14 19:11:44 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/parser.h"

int		is_filename(t_tkn **tkn)
{
	ft_putstr("filename token = ");
	ft_putendl((*tkn)->data);
	if (*tkn && (*tkn)->type == CHR_WORD)
	{
		*tkn = (*tkn)->next;
		return (1);
	}
	return (0);
}

int		is_here_end(t_tkn **tkn)
{
	ft_putstr("here end token = ");
	ft_putendl((*tkn)->data);
	if (*tkn && ((*tkn)->type == CHR_WORD))
	{
		*tkn = (*tkn)->next;
		return (1);
	}
	return (0);
}

int		is_io_here(t_tkn **tkn)
{
	if (*tkn && ((*tkn)->type == CHR_DLESS
		|| (*tkn)->type == CHR_DLESSDASH))
	{
		ft_putstr("DLESS or DLESSASH token = ");
		ft_putendl((*tkn)->data);
		*tkn = (*tkn)->next;
		return (is_here_end(tkn) ? 1 : 0);
	}
	else
		return (0);
}

int		is_io_file(t_tkn **tkn)
{
	if (*tkn && ((*tkn)->type == CHR_LESS
		|| (*tkn)->type == CHR_LESSAND
		|| (*tkn)->type == CHR_GREAT
		|| (*tkn)->type == CHR_GREATAND
		|| (*tkn)->type == CHR_DGREAT
		|| (*tkn)->type == CHR_LESSGREAT
		|| (*tkn)->type == CHR_CLOBBER))
	{
		ft_putstr("IO FILE token = ");
		ft_putendl((*tkn)->data);
		*tkn = (*tkn)->next;
		return (is_filename(tkn) ? 1 : 0);
	}
	else
		return (0);
}

int		is_io_redirect(t_tkn **tkn)
{
	if (*tkn && (*tkn)->type == CHR_IO_NUMBER)
		*tkn = (*tkn)->next;
	if (*tkn && is_io_file(tkn))
		return (1);
	else if (*tkn && is_io_here(tkn))
		return (1);
	else
		return (0);
}
