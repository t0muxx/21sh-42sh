/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 11:28:09 by tmaraval          #+#    #+#             */
/*   Updated: 2018/06/25 13:44:03 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "utils.h"

void	input_backspace(t_buffer *tbuffer, char *read_buf)
{
	if (ft_strlen(read_buf) == 1 && read_buf[0] == 127)
	{
		if (tbuffer->cnt != 0)
		{
			line_reset(tbuffer);
			string_delete_char(&(tbuffer->buffer), tbuffer->cnt - 1);
			cursor_move_left(tbuffer, 1);
			cursor_save_pos(tbuffer);
			line_go_begin(tbuffer);
			tbuffer->cnt = 0;
			tbuffer->index = 0;
			tputs(tbuffer->termcap->cd, 0, ft_putcc);
			prompt_print(tbuffer);
			insert_tbuffer(tbuffer);
			cursor_reload_pos(tbuffer);
		}
	}
}

void	input_delete(t_buffer *tbuffer, char *read_buf)
{
	if (ft_memcmp(read_buf, FT_KEY_DEL, ft_strlen(FT_KEY_DEL)) == 0)
	{
		line_reset(tbuffer);
		string_delete_char(&(tbuffer->buffer), tbuffer->cnt);
		cursor_save_pos(tbuffer);
		line_go_begin(tbuffer);
		tbuffer->cnt = 0;
		tbuffer->index = 0;
		tputs(tbuffer->termcap->cd, 0, ft_putcc);
		prompt_print(tbuffer);
		insert_tbuffer(tbuffer);
		cursor_reload_pos(tbuffer);
	}
}

void	input_home(t_buffer *tbuffer, char *read_buf)
{
	if (ft_memcmp(read_buf, FT_KEY_HOME, ft_strlen(FT_KEY_HOME)) == 0)
	{
		line_reset(tbuffer);
		line_go_begin(tbuffer);
		tputs(tbuffer->termcap->nd, 0, ft_putcc);
		tputs(tbuffer->termcap->nd, 0, ft_putcc);
		tputs(tbuffer->termcap->nd, 0, ft_putcc);
		tbuffer->index = 0;
		tbuffer->cnt = 0;
	}
}

void	input_end(t_buffer *tbuffer, char *read_buf)
{
	if (ft_memcmp(read_buf, FT_KEY_END, ft_strlen(FT_KEY_END)) == 0)
	{
		line_reset(tbuffer);
		cursor_move_right(tbuffer,
		(int)ft_strlen(tbuffer->buffer) - tbuffer->cnt);
	}
}

void	input_shift_right_left(t_buffer *tbuffer, char *read_buf)
{
	if (ft_memcmp(read_buf, FT_KEY_SHIFT_LEFT,
	ft_strlen(FT_KEY_SHIFT_LEFT)) == 0)
	{
		line_reset(tbuffer);
		cursor_move_left_next_word(tbuffer);
	}
	if (ft_memcmp(read_buf, FT_KEY_SHIFT_RIGHT,
	ft_strlen(FT_KEY_SHIFT_RIGHT)) == 0)
	{
		line_reset(tbuffer);
		cursor_move_right_next_word(tbuffer);
	}
}
