/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_arrow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 15:57:53 by tmaraval          #+#    #+#             */
/*   Updated: 2018/04/10 10:28:04 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	input_arrow_left(t_buffer *tbuffer, char *read_buf)
{
	if (ft_memcmp(read_buf, FT_KEY_LEFT, ft_strlen(FT_KEY_LEFT)) == 0)
	{
		line_reset(tbuffer);
		cursor_move_left(tbuffer, 1);
	}
}

void	input_arrow_right(t_buffer *tbuffer, char *read_buf)
{
	if (ft_memcmp(read_buf, FT_KEY_RIGHT, ft_strlen(FT_KEY_RIGHT)) == 0)
	{
		line_reset(tbuffer);
		cursor_move_right(tbuffer, 1);
	}
}

void	input_arrow_up(t_buffer *tbuffer, char *read_buf)
{
	t_cmd_hist **head;

	head = tbuffer->head_hist;
	if (ft_memcmp(read_buf, FT_KEY_UP, ft_strlen(FT_KEY_UP)) == 0)
	{
		history_print(tbuffer, &((*head)->oldest));
	}
}

void	input_arrow_down(t_buffer *tbuffer, char *read_buf)
{
	t_cmd_hist **head;

	head = tbuffer->head_hist;
	if (ft_memcmp(read_buf, FT_KEY_DOWN, ft_strlen(FT_KEY_DOWN)) == 0)
	{
		history_print(tbuffer, &((*head)->newest));
	}
}

void	input_arrow_shift_updown(t_buffer *tbuffer, char *read_buf)
{
	if (ft_memcmp(read_buf, FT_KEY_SHIFT_UP, ft_strlen(FT_KEY_SHIFT_UP)) == 0)
	{
		line_reset(tbuffer);
		if (tbuffer->cnt < tbuffer->colnbr)
			cursor_move_left(tbuffer, tbuffer->cnt);
		else
			cursor_move_left(tbuffer, tbuffer->colnbr);
	}
	if (ft_memcmp(read_buf, FT_KEY_SHIFT_DOWN,
	ft_strlen(FT_KEY_SHIFT_DOWN)) == 0)
	{
		line_reset(tbuffer);
		if (tbuffer->cnt + tbuffer->colnbr <
		(int)ft_strlen(tbuffer->buffer))
			cursor_move_right(tbuffer, tbuffer->line == 1 ?
			tbuffer->colnbr : tbuffer->colnbr);
		else
			cursor_move_right(tbuffer, (int)ft_strlen(tbuffer->buffer));
	}
}
