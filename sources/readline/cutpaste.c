/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutpaste.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 08:54:47 by tmaraval          #+#    #+#             */
/*   Updated: 2018/09/06 15:35:09 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "utils.h"

void	input_select_left(t_buffer *tbuffer, char *read_buf)
{
	char cur_char;

	if (ft_memcmp(read_buf, FT_KEY_ALT_LEFT,
	ft_strlen(FT_KEY_ALT_LEFT)) == 0)
	{
		if (tbuffer->cutend == -1)
			tbuffer->cutend = tbuffer->cnt;
		if (tbuffer->cnt > 0)
		{
			cur_char = tbuffer->buffer[tbuffer->cnt - 1];
			cursor_move_left(tbuffer, 1);
			tputs(tbuffer->termcap->so, 0, ft_putcc);
			write(1, &cur_char, 1);
			tbuffer->cnt++;
			tbuffer->index++;
			cursor_move_left(tbuffer, 1);
			tputs(tbuffer->termcap->se, 0, ft_putcc);
			tbuffer->cutstart = tbuffer->cnt;
		}
	}
}

void	input_select_right(t_buffer *tbuffer, char *read_buf)
{
	char cur_char;

	if (ft_memcmp(read_buf, FT_KEY_ALT_RIGHT,
	ft_strlen(FT_KEY_ALT_RIGHT)) == 0)
	{
		if (tbuffer->cutstart == -1)
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

void	input_copy(t_buffer *tbuffer, char *read_buf)
{
	if (read_buf[0] == 11)
	{
		ft_memcpy(tbuffer->cutbuffer,
		tbuffer->buffer + tbuffer->cutstart,
		tbuffer->cutend - tbuffer->cutstart);
//		ft_printf("\ncutstar |%d|\n", tbuffer->cutstart);
//		ft_printf("\ncutend |%d|\n", tbuffer->cutend);
		line_reset(tbuffer);
	}
}

void	input_cut(t_buffer *tbuffer, char *read_buf)
{
	int i;

	i = 0;
	if (read_buf[0] == 24)
	{
		ft_memcpy(tbuffer->cutbuffer, tbuffer->buffer + tbuffer->cutstart,
		tbuffer->cutend - tbuffer->cutstart);
		while (i++ < (tbuffer->cutend - tbuffer->cutstart))
			string_delete_char(&tbuffer->buffer, tbuffer->cutstart);
		line_reset(tbuffer);
	}
}

void	input_paste(t_buffer *tbuffer, char *read_buf)
{
	int i;

	i = 0;
	if (read_buf[0] == 16)
	{
		string_insert_substring(&(tbuffer->buffer), tbuffer->cutbuffer, tbuffer->cnt);
		line_reset(tbuffer);
	}
}
