/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_tbuffer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 09:47:52 by tmaraval          #+#    #+#             */
/*   Updated: 2018/03/01 13:34:13 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <termcap.h>
#include <term.h>
#include <cursor.h>

void	cursor_move_left_upd_tbuffer(int count, t_buffer *tbuffer)
{
	char	*temp;

//	ft_printf("\n|cnt = %d index = %d line = %d colnbr = %d|\n", tbuffer->cnt, tbuffer->index, tbuffer->line, tbuffer->colnbr);
	if (tbuffer->cnt != 0 && tbuffer->index == 1)	
	{
		tbuffer->line--;
		tbuffer->index--;
		temp = tgetstr("up", NULL);
		tputs(temp, 0, ft_putcc);
		cursor_move_right(tbuffer->colnbr + 1);
		if (tbuffer->line == 1)
			tbuffer->colnbr -= 3;
		tbuffer->index = tbuffer->colnbr;
	}
	else
	{
		tbuffer->index--;
		cursor_move_left(count);
	}
}

void	cursor_move_right_upd_tbuffer(int count, t_buffer *tbuffer)
{
	
	char *temp;

	//ft_printf("%d|%d", *index, colnbr);
	if (tbuffer->index == tbuffer->colnbr)
	{
		temp = tgetstr("do", NULL);
		tputs(temp, 0, ft_putcc);
		tbuffer->index = 1;
		tbuffer->line++;
		if (tbuffer->line == 2)
			tbuffer->colnbr += 3;
	}
	else
	{
		tbuffer->index++;
		cursor_move_right(count);
	}
}
