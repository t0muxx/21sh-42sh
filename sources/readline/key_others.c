/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_others.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 08:39:08 by tmaraval          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2018/03/29 11:51:43 by tmaraval         ###   ########.fr       */
=======
/*   Updated: 2018/03/28 14:57:14 by tmaraval         ###   ########.fr       */
>>>>>>> parent of 2972295... reworked backspace and left arrow to mactch if state quote
/*                                                                            */
/* ************************************************************************** */

#include "key.h"
#include "cursor.h"
#include <term.h>

void	key_select_buffer(t_buffer *tbuffer)
{
	char	buf[3];
	char	cur_char;

	ft_bzero(buf, 3);
	if (tbuffer->c_buf == 27 && tbuffer->state == READ_NORMAL)
	{
		read(0, buf, 3);
		if (buf[0] == '[' && buf[1] == 'D')
		{
			if (tbuffer->cutend == 0)
				tbuffer->cutend = tbuffer->cnt;
			if (tbuffer->cnt > 0)
			{
				cur_char = tbuffer->buffer[tbuffer->cnt - 1];
				cursor_move_left_upd_tbuffer(1, tbuffer);
				tputs(tbuffer->termcap->so, 0, ft_putcc);
				write(1, &cur_char, 1);
				tbuffer->cnt++;
				tbuffer->index++;
				cursor_move_left_upd_tbuffer(1, tbuffer);
				tputs(tbuffer->termcap->se, 0, ft_putcc);
				tbuffer->cutstart = tbuffer->cnt;

			}
		}
		if (buf[0] == '[' && buf[1] == 'C' && tbuffer->state == READ_NORMAL)
		{
			if (tbuffer->cutstart == 0 && tbuffer->cutend == 0)
				tbuffer->cutstart = tbuffer->cnt;
			if (tbuffer->cnt < (int)ft_strlen(tbuffer->buffer))
			{
				cur_char = tbuffer->buffer[tbuffer->cnt];
				tputs(tbuffer->termcap->so, 0, ft_putcc);
				write(1, &cur_char, 1);
				tbuffer->cnt++;
				tbuffer->index++;
				tputs(tbuffer->termcap->se, 0, ft_putcc);
				tbuffer->cutend = tbuffer->cnt;
			}
		}
	}
}

void	key_group(t_buffer *tbuffer, t_cmd_hist **head)
{
	read(0, &tbuffer->c_buf, 1);
//	ft_printf("%d\n", tbuffer->c_buf);
	key_select_buffer(tbuffer);
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
			cur_cnt = 0;
			cur_cnt = tbuffer->cnt;
			cursor_move_left_upd_tbuffer(BUFFER_SIZE, tbuffer);
			string_delete_char(&(tbuffer->buffer), cur_cnt - 1);
			tputs(tbuffer->termcap->cd, 0, ft_putcc);
			readline_print_prompt(tbuffer, TRUE);
			tbuffer->cnt = 0;
			tbuffer->index = 0;
			readline_print_upd_tbuffer(tbuffer);
			cur_cnt--;
			cursor_move_left_upd_tbuffer(((int)ft_strlen(tbuffer->buffer))
			- cur_cnt, tbuffer);
		}
<<<<<<< HEAD
=======
	//	write(1, "\n\n\n\n++++++++++++++++koekeofoekfoekfoekfokfeokfoekfoekf\n\n", 25);
	}
	else if (tbuffer->state != READ_NORMAL)
	{
		if (tbuffer->index > 0)
		{
			cur_pos = 0;
			cur_cnt = 0;
			cur_cnt = tbuffer->cnt;
			cursor_move_left_upd_tbuffer(tbuffer->index + 2, tbuffer);
			string_delete_char(&(tbuffer->buffer), cur_cnt - 1);
			tputs(tbuffer->termcap->cd, 0, ft_putcc);
			readline_print_prompt(tbuffer, TRUE);
			tbuffer->index = 0;
			tbuffer->cnt += 2;
			while (tbuffer->buffer[tbuffer->cnt] != '\n' && tbuffer->buffer[tbuffer->cnt] != '\0')
			{
				write(1, &(tbuffer->buffer[tbuffer->cnt]), 1);
				tbuffer->cnt++;
				tbuffer->index++;
			}
		}
	}
	else
		;
>>>>>>> parent of 2972295... reworked backspace and left arrow to mactch if state quote
}

void	key_do_home_end(t_buffer *tbuffer)
{
	if (tbuffer->c_buf == 'H' && tbuffer->state == READ_NORMAL)
	{
		cursor_move_left_upd_tbuffer(tbuffer->cnt, tbuffer);
		tbuffer->cnt = 0;
		tbuffer->index = 0;
	}
	if (tbuffer->c_buf == 'F' && tbuffer->state == READ_NORMAL)
		cursor_move_right_upd_tbuffer(
		(int)ft_strlen(tbuffer->buffer) - tbuffer->cnt, tbuffer);
}

void	key_do_del(t_buffer *tbuffer)
{
	int cur_cnt;

	if (tbuffer->c_buf == '3')
	{
		read(0, &(tbuffer->c_buf), 1);
		if (tbuffer->c_buf == '~')
		{
			if (tbuffer->cnt < (int)ft_strlen(tbuffer->buffer) && tbuffer->state == READ_NORMAL)
			{
				cur_cnt = 0;
				cur_cnt = tbuffer->cnt;
				string_delete_char(&(tbuffer->buffer), tbuffer->cnt);
				cursor_move_left_upd_tbuffer(BUFFER_SIZE, tbuffer);
				tputs(tbuffer->termcap->cd, 0, ft_putcc);
				readline_print_prompt(tbuffer, TRUE);
				tbuffer->cnt = 0;
				tbuffer->index = 0;
				readline_print_upd_tbuffer(tbuffer);
				cursor_move_left_upd_tbuffer((
				(int)ft_strlen(tbuffer->buffer)) - cur_cnt, tbuffer);
			}
		}
	}
}
