/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 04:49:53 by cormarti          #+#    #+#             */
/*   Updated: 2018/06/01 01:36:15 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/parser.h"

int		is_pipe_seq(t_tkn **tkn)
{
	if (*tkn == NULL || !is_command(tkn))
		return (0);
	if ((*tkn)->type == CHR_PIPE)
	{
		ft_putstr("PIPE token = ");
		ft_putendl((*tkn)->data);
		*tkn = (*tkn)->next;
		if (*tkn && is_command(tkn))
		{
			if (*tkn && is_pipe_seq(tkn))
				return (1);
			else
				return (0);
		}
		else
			return (0);
	}
	else
		return (0);
}

int		is_pipeline(t_tkn **tkn)
{
	if (is_pipe_seq(tkn))
		return (1);
	else
		return (0);
}
