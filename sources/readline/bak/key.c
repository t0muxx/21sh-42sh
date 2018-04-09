/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 09:20:02 by tmaraval          #+#    #+#             */
/*   Updated: 2018/03/28 14:14:58 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key.h"
#include "cursor.h"
#include <term.h>

void	key_do_shift_updown(t_buffer *tbuffer, char buf[4])
{
	if (buf[0] == ';' && buf[1] == '2' && buf[2] == 'A')
	{
		if (tbuffer->cnt < tbuffer->colnbr)
			cursor_move_left_upd_tbuffer(tbuffer->cnt, tbuffer);
		else
			cursor_move_left_upd_tbuffer(tbuffer->colnbr, tbuffer);
	}
	if (buf[0] == ';' && buf[1] == '2' && buf[2] == 'B')
	{
		if (tbuffer->cnt + tbuffer->colnbr <
		(int)ft_strlen(tbuffer->buffer))
			cursor_move_right_upd_tbuffer(tbuffer->line == 1 ?
			tbuffer->colnbr + 3 : tbuffer->colnbr, tbuffer);
		else
			cursor_move_right_upd_tbuffer(
			(int)ft_strlen(tbuffer->buffer), tbuffer);
	}
}

void	key_do_shift_arrow(t_buffer *tbuffer)
{
	char	buf[4];

	ft_bzero(buf, 4);
	if (tbuffer->c_buf == '1')
	{
		read(0, buf, 3);
		key_do_shift_updown(tbuffer, buf);
		if (buf[0] == ';' && buf[1] == '2' && buf[2] == 'D')
			cursor_move_left_next_word(tbuffer);
		if (buf[0] == ';' && buf[1] == '2' && buf[2] == 'C')
			cursor_move_right_next_word(tbuffer);
	}
}

void	key_do_arrow(t_buffer *tbuffer, t_cmd_hist **head)
{
	cursor_reset_line(tbuffer);
	if (tbuffer->c_buf == 'A')
		readline_history_print(head, (*head)->oldest, tbuffer);
	if (tbuffer->c_buf == 'B')
		readline_history_print(head, (*head)->newest, tbuffer);
	if (tbuffer->c_buf == 'C')
	{
		if (tbuffer->cnt < (int)ft_strlen(tbuffer->buffer))
			cursor_move_right_upd_tbuffer(1, tbuffer);
	}
	if (tbuffer->c_buf == 'D')
	{
		if (tbuffer->state == READ_NORMAL)
		{
			if (tbuffer->cnt > 0)
				cursor_move_left_upd_tbuffer(1, tbuffer);
		}
		else
		{
			if (tbuffer->index > 0)
				cursor_move_left_upd_tbuffer(1, tbuffer);
		}
	}
}
