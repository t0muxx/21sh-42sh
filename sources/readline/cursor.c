/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 18:35:06 by tmaraval          #+#    #+#             */
/*   Updated: 2018/04/04 10:44:18 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	cursor_move_left(t_buffer *tbuffer, int cnt)
{
	if (tbuffer->state == READ_NORMAL)
	{
		while (cnt > 0 && tbuffer->cnt > 0)
		{
			if (tbuffer->line > 1 && tbuffer->index == 0)
			{
				tputs(tbuffer->termcap->up, 0, ft_putcc);
				tbuffer->line--;
				if (tbuffer->line == 1)
					tbuffer->prompt_len = 3;
				tbuffer->cnt--;
				line_go_end(tbuffer);
				tbuffer->index = tbuffer->colnbr - tbuffer->prompt_len - 1;
			}
			else
			{
				tputs(tbuffer->termcap->le, 0, ft_putcc);
				tbuffer->index--;
				tbuffer->cnt--;
			}
			cnt--;
		}
	}
}

void	cursor_move_right(t_buffer *tbuffer, int cnt)
{
	if (tbuffer->state == READ_NORMAL)
	{
		while (cnt > 0 && tbuffer->cnt < (int)ft_strlen(tbuffer->buffer))
		{
			if (tbuffer->index + tbuffer->prompt_len == tbuffer->colnbr - 1)
			{
				line_go_down(tbuffer, 1);
				tbuffer->cnt++;
			}
			else
			{
				tputs(tbuffer->termcap->nd, 0, ft_putcc);
				tbuffer->cnt++;
				tbuffer->index++;
			}
			cnt--;
		}
	}
}

void	cursor_move_left_next_word(t_buffer *tbuffer)
{
	int i;

	i = tbuffer->cnt - 1;
	while (i >= 0)
	{
		if (tbuffer->buffer[i] == ' ')
		{
			while (tbuffer->buffer[i] == ' ')
				i--;
			cursor_move_left(tbuffer, tbuffer->cnt - i - 1);
			break ;
		}
		i--;
	}
}

void	cursor_move_right_next_word(t_buffer *tbuffer)
{
	int i;

	i = tbuffer->cnt;
	while (i < (int)ft_strlen(tbuffer->buffer))
	{
		if (tbuffer->buffer[i] == ' ')
		{
			while (tbuffer->buffer[i] == ' ')
				i++;
			cursor_move_right(tbuffer, i - tbuffer->cnt);
			break ;
		}
		i++;
	}
}
