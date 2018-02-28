/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 08:17:44 by tmaraval          #+#    #+#             */
/*   Updated: 2018/02/28 09:17:22 by tomlulu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <termcap.h>
#include <term.h>
#include "cursor.h"

void	cursor_move_left(int count)
{
	char *temp;

	temp = tgetstr("le", NULL);
	while (count)
	{
		tputs(temp, 0, ft_putcc);
		count--;
	}
}

/*
 ** cursor_move_left move the cursor from count line to the left
 ** using the ansi escape code
*/

void	cursor_move_left_upd_tbuffer(int count, t_buffer *tbuffer)
{
	char	*temp;
	int	cnt;

	//ft_printf("\n|cnt = %d index = %d line = %d colnbr = %d|\n", tbuffer->cnt, tbuffer->index, tbuffer->line, tbuffer->colnbr);
	cnt = 0;
	if (tbuffer->cnt != 0 && tbuffer->index == 1)	
	{
		tbuffer->line--;
		tbuffer->index--;
		temp = tgetstr("up", NULL);
		tputs(temp, 0, ft_putcc);
		temp = tgetstr("nd", NULL);
		while (cnt <= (tbuffer->colnbr + 1))
		{
			tputs(temp, 0, ft_putcc);
			cnt++;
		}
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

/*
 ** cursor_move_right move the cursor from count line to the right
 ** using the ansi escape code
*/

void	cursor_move_right(int count, t_buffer *tbuffer)
{
	
	char *temp;

	//ft_printf("%d|%d", *index, colnbr);
	if (tbuffer->index == tbuffer->colnbr)
	{
	//	ft_printf("?");
		ft_putstr("\033E");
		tbuffer->index = 0;
		tbuffer->line++;
		if (tbuffer->line == 2)
			tbuffer->colnbr += 3;
	}
	else
	{
		tbuffer->index++;
		temp = tgetstr("nd", NULL);
		while (count)
		{
			tputs(temp, 0, ft_putcc);
			count--;
		}
	}
}

void	cursor_save_pos(void)
{
	char	*ret;

	if ((ret = tgetstr("sc", NULL)) == NULL)
	{
		ft_putstr_fd("Error termcaps\n", 2);
		return ;
	}
	ft_putstr(ret);
}

void	cursor_reload_pos(void)
{
	char	*ret;

	if ((ret = tgetstr("rc", NULL)) == NULL)
	{
		ft_putstr_fd("Error termcaps\n", 2);
		return ;
	}
	ft_putstr(ret);
}
