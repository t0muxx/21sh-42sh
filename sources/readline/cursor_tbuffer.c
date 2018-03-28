/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_tbuffer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 09:47:52 by tmaraval          #+#    #+#             */
/*   Updated: 2018/03/28 10:21:07 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <termcap.h>
#include <term.h>
#include <cursor.h>

void	cursor_move_left_upd_tbuffer(int count, t_buffer *tbuffer)
{
	int		prompt_len;

	prompt_len = readline_print_prompt(tbuffer, FALSE);
	while (count > 0 && tbuffer->cnt > -3)
	{
		if (tbuffer->line != 1 && tbuffer->cnt != 1 && tbuffer->index == 0)
		{
			tbuffer->line--;
			tputs(tbuffer->termcap->up, 0, ft_putcc);
			cursor_move_right(tbuffer->colnbr + 1);
			if (tbuffer->line == 1)
				tbuffer->colnbr -= prompt_len;
			tbuffer->index = tbuffer->colnbr;
			tbuffer->index--;
		}
		else
		{
			tbuffer->index--;
			tputs(tbuffer->termcap->le, 0, ft_putcc);
		}
		tbuffer->cnt--;
		count--;
	}
}

void	cursor_move_right_upd_tbuffer(int count, t_buffer *tbuffer)
{
	int		prompt_len;

	prompt_len = readline_print_prompt(tbuffer, FALSE);
	while (count && tbuffer->cnt < (int)ft_strlen(tbuffer->buffer))
	{
		if (tbuffer->index == tbuffer->colnbr - 1)
		{
			tputs(tbuffer->termcap->sf, 0, ft_putcc);
			tbuffer->index = 0;
			tbuffer->line++;
			if (tbuffer->line == 2)
				tbuffer->colnbr += prompt_len;
		}
		else
		{
			tbuffer->index++;
			tputs(tbuffer->termcap->nd, 0, ft_putcc);
		}
		count--;
		tbuffer->cnt++;
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
			cursor_move_left_upd_tbuffer(tbuffer->cnt - i - 1, tbuffer);
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
			cursor_move_right_upd_tbuffer(i - tbuffer->cnt, tbuffer);
			break ;
		}
		i++;
	}
}
