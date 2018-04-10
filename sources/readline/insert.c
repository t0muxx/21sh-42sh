/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 17:45:57 by tmaraval          #+#    #+#             */
/*   Updated: 2018/04/10 10:26:55 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	insert_tbuffer(t_buffer *tbuffer)
{
	int i;

	i = 0;
	while (tbuffer->buffer[tbuffer->cnt])
	{
		write(1, &tbuffer->buffer[tbuffer->cnt], 1);
		tbuffer->cnt++;
		tbuffer->index++;
		if (tbuffer->index + tbuffer->prompt_len == tbuffer->colnbr)
			line_go_down(tbuffer, 1);
	}
}

void	insert_char(t_buffer *tbuffer, char *read_buf)
{
	if (ft_strlen(read_buf) == 1 && read_buf[0] != 127
	&& read_buf[0] > 24 && read_buf[0] != '\n')
	{
		if (tbuffer->buffer[tbuffer->cnt] == 0)
		{
			tbuffer->buffer[tbuffer->cnt++] = read_buf[0];
			tbuffer->index++;
			write(1, read_buf, 1);
			if (tbuffer->index + tbuffer->prompt_len == tbuffer->colnbr)
				line_go_down(tbuffer, 1);
		}
		else if (tbuffer->state != READ_IN_QUOTE)
		{
			cursor_save_pos(tbuffer);
			string_shift_right(&(tbuffer->buffer), tbuffer->cnt);
			tbuffer->buffer[tbuffer->cnt] = read_buf[0];
			line_go_begin(tbuffer);
			prompt_print(tbuffer);
			tbuffer->cnt = 0;
			tbuffer->index = 0;
			insert_tbuffer(tbuffer);
			cursor_reload_pos(tbuffer);
			cursor_move_right(tbuffer, 1);
		}
	}
}

void	input_enter(t_buffer *tbuffer, char *read_buf)
{
	if (read_buf[0] == '\n')
		tbuffer->state = READ_PROCESS;
}
