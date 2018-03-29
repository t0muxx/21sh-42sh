/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 10:18:53 by tmaraval          #+#    #+#             */
/*   Updated: 2018/03/29 09:27:22 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include <term.h>
#include <cursor.h>

int		readline_print_prompt(t_buffer *tbuffer, int print)
{
	char *prompt;

	prompt = "$> ";
	if (print == TRUE && (tbuffer->state == READ_NORMAL || tbuffer->line == 1))
		ft_putstr(prompt);
	else if (print == TRUE && tbuffer->state != READ_NORMAL)
	{
		ft_putstr("> ");
		term_get_colnbr(tbuffer);
	}
	else
		;
	return ((int)ft_strlen(prompt));
}

void	readline_print_char_upd_tbuffer(t_buffer *tbuffer, char toprint)
{
	write(1, &(toprint), 1);
	if (tbuffer->index == tbuffer->colnbr - 1)
	{
		tbuffer->line++;
		tbuffer->index = -1;
		if (tbuffer->line == 2)
			tbuffer->colnbr += 3;
		tputs(tbuffer->termcap->sf, 0, ft_putcc);
	}
	tbuffer->index++;
	tbuffer->cnt++;
}

void	readline_print_upd_tbuffer(t_buffer *tbuffer)
{
	int i;

	i = 0;
	while (tbuffer->buffer[i])
	{
		readline_print_char_upd_tbuffer(tbuffer, tbuffer->buffer[i]);
		i++;
	}
}

/*
** readline_print_n_buf manage if its the last char on the line
** it print it and add it to the buffer
** if its not the last char it will shift the buffer on the right
** in order to get a blank space for the char to add (line edition)
*/

void	readline_print_n_buf(t_buffer *tbuffer)
{
	int		cur_cnt;

	cur_cnt = 0;
	if (tbuffer->buffer[tbuffer->cnt] != 0 && tbuffer->state == READ_NORMAL)
	{
		cur_cnt = tbuffer->cnt;
		string_shift_right(&(tbuffer->buffer), tbuffer->cnt);
		cursor_move_left_upd_tbuffer(BUFFER_SIZE, tbuffer);
		tbuffer->buffer[cur_cnt] = tbuffer->c_buf;
		readline_print_prompt(tbuffer, TRUE);
		tbuffer->cnt = 0;
		tbuffer->index = 0;
		readline_print_upd_tbuffer(tbuffer);
		cur_cnt++;
		cursor_move_left_upd_tbuffer(
		((int)ft_strlen(tbuffer->buffer) - cur_cnt), tbuffer);
	}
	else
	{
		tbuffer->buffer[tbuffer->cnt] = tbuffer->c_buf;
		readline_print_char_upd_tbuffer(tbuffer, tbuffer->c_buf);
	}
}

void	readline_print_cutbuffer(t_buffer *tbuffer)
{
	int j;
	int i;

	i = 0;
	j = 0;
	if (tbuffer->cnt == (int)ft_strlen(tbuffer->buffer))
		ft_strcat(tbuffer->buffer, tbuffer->cutbuffer);
	else
	{
		j = tbuffer->cnt;
		while (tbuffer->cutbuffer[i])
		{
			string_shift_right(&tbuffer->buffer, j);
			tbuffer->buffer[j++] = tbuffer->cutbuffer[i++];
		}
			cursor_move_right_upd_tbuffer(j, tbuffer);
	}
	cursor_reset_line(tbuffer);
	ft_bzero(tbuffer->cutbuffer, BUFFER_SIZE);
	tbuffer->cutstart = 0;
	tbuffer->cutend = 0;
}
