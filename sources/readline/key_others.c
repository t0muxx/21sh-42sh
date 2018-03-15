/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_others.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 08:39:08 by tmaraval          #+#    #+#             */
/*   Updated: 2018/03/15 09:54:44 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key.h"
#include "cursor.h"
#include <term.h>


void	key_do_shift_arrow(t_buffer *tbuffer)
{
	char	buf[4];

	ft_bzero(buf, 4);
	if (tbuffer->c_buf == '1')
	{
		read(0, buf, 3);
		if (buf[0] == ';' && buf[1] == '2' && buf[2] == 'A')
		{
				if (tbuffer->cnt < tbuffer->colnbr)
					cursor_move_left_upd_tbuffer(tbuffer->cnt, tbuffer);
				else
					cursor_move_left_upd_tbuffer(tbuffer->colnbr, tbuffer);
		}
		if (buf[0] == ';' && buf[1] == '2' && buf[2] == 'B')
		{
			if (tbuffer->cnt + tbuffer->colnbr < (int)ft_strlen(tbuffer->buffer))
				cursor_move_right_upd_tbuffer(tbuffer->line == 1 ? tbuffer->colnbr + 3 : tbuffer->colnbr, tbuffer);
			else
				cursor_move_right_upd_tbuffer((int) ft_strlen(tbuffer->buffer), tbuffer);
		}
		if (buf[0] == ';' && buf[1] == '2' && buf[2] == 'D')
				cursor_move_left_next_word(tbuffer);
		if (buf[0] == ';' && buf[1] == '2' && buf[2] == 'C')
				cursor_move_right_next_word(tbuffer);
		}
}

void	key_group(t_buffer *tbuffer, t_cmd_hist *head)
{
	read(0, &(tbuffer->c_buf), 1);
	if (tbuffer->c_buf == '[')
	{
		read(0, &(tbuffer->c_buf), 1);
		key_do_shift_arrow(tbuffer);	
		key_do_arrow(tbuffer, head);
		key_do_home_end(tbuffer);
		key_do_del(tbuffer);
	}
}

void	key_do_backspace(t_buffer *tbuffer)
{
	int cur_cnt;

	if (tbuffer->cnt > 0)
	{
	//ft_printf("\n|cnt = %d index = %d line = %d colnbr = %d|\n", tbuffer.cnt, tbuffer.index, tbuffer.line, tbuffer.colnbr);
		cur_cnt = 0;
		cur_cnt = tbuffer->cnt;
		cursor_move_left_upd_tbuffer(BUFFER_SIZE, tbuffer);
		string_delete_char(&(tbuffer->buffer), cur_cnt - 1);
		tputs(tbuffer->termcap->cd, 0, ft_putcc);
		readline_print_prompt(TRUE);
		tbuffer->cnt = 0;
		tbuffer->index = 0;
		readline_print_upd_tbuffer(tbuffer);
		cur_cnt--;
		cursor_move_left_upd_tbuffer(((int)ft_strlen(tbuffer->buffer)) - cur_cnt, tbuffer);
		//cursor_move_left_upd_tbuffer(1, &tbuffer);
		//	cursor_up_line((ft_strlen(tbuffer.buffer) / tbuffer.colnbr) - 1);
		}
}

void	key_do_home_end(t_buffer *tbuffer)
{
	if (tbuffer->c_buf == 'H')
	{
		cursor_move_left_upd_tbuffer(tbuffer->cnt, tbuffer);
		tbuffer->cnt = 0;
		tbuffer->index = 0;
	}
	if (tbuffer->c_buf == 'F')
		cursor_move_right_upd_tbuffer((int)ft_strlen(tbuffer->buffer) - tbuffer->cnt, tbuffer);
}

void	key_do_del(t_buffer *tbuffer)
{
	int cur_cnt;

	if (tbuffer->c_buf == '3')
	{
		read(0, &(tbuffer->c_buf), 1);
		if (tbuffer->c_buf == '~')
		{
			if (tbuffer->cnt < (int)ft_strlen(tbuffer->buffer))
			{
				cur_cnt = 0;
				cur_cnt = tbuffer->cnt;
				string_delete_char(&(tbuffer->buffer), tbuffer->cnt);
				cursor_move_left_upd_tbuffer(BUFFER_SIZE, tbuffer);
				tputs(tbuffer->termcap->cd, 0, ft_putcc);
				readline_print_prompt(TRUE);
				tbuffer->cnt = 0;
				tbuffer->index = 0;
				readline_print_upd_tbuffer(tbuffer);
				cursor_move_left_upd_tbuffer(((int)ft_strlen(tbuffer->buffer)) - cur_cnt, tbuffer);
			}
		}
	}
}
