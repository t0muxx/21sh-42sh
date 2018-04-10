/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 08:52:02 by tmaraval          #+#    #+#             */
/*   Updated: 2018/04/10 10:21:03 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	cursor_save_pos(t_buffer *tbuffer)
{
	tbuffer->curs_pos = tbuffer->cnt;
}

void	cursor_reload_pos(t_buffer *tbuffer)
{
	if (tbuffer->curs_pos < tbuffer->cnt)
	{
		cursor_move_left(tbuffer, tbuffer->cnt - tbuffer->curs_pos);
	}
	if (tbuffer->curs_pos > tbuffer->cnt)
	{
		while (tbuffer->curs_pos)
		{
			cursor_move_right(tbuffer, 1);
			tbuffer->curs_pos--;
		}
	}
}
