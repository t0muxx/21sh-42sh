/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 08:17:44 by tmaraval          #+#    #+#             */
/*   Updated: 2018/02/26 17:19:51 by tomlulu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <termcap.h>
#include <term.h>
#include "cursor.h"
/*
 ** cursor_move_left move the cursor from count line to the left
 ** using the ansi escape code
*/

int	ft_putcc(int c)
{
	write(1, &c, 1);
	return (0);
}

void	cursor_move_left(int count, t_buffer *tbuffer)
{
	char	*temp;
	int	cnt;

	//ft_printf("\n|cnt = %d index = %d line = %d colnbr = %d|\n", tbuffer->cnt, tbuffer->index, tbuffer->line, tbuffer->colnbr);
	cnt = 0;
	if (tbuffer->cnt != 0 && tbuffer->index == 1)	
	{
		tbuffer->line--;
		tbuffer->index = tbuffer->colnbr;
		if (tgetflag("bw") == 0)
		{
			tbuffer->index--;
			temp = tgetstr("up", NULL);
			tputs(temp, 0, ft_putcc);
			temp = tgetstr("nd", NULL);
			while (cnt < (tbuffer->colnbr + 2))
			{
				tputs(temp, 0, ft_putcc);
				cnt++;
			}
		}
		if (tbuffer->line == 1)
			tbuffer->colnbr -= 3;
	}
	tbuffer->index--;
	temp = tgetstr("le", NULL);
	while (count)
	{
		tputs(temp, 0, ft_putcc);
		count--;
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
		tbuffer->index++;
	ft_putstr("\033[");
	temp = ft_itoa(count);
	ft_putstr(temp);
	ft_putstr("C");
	free(temp);
	
	/*char	*ret;
	char	*ret2;

	if ((ret = tgetstr("nd", NULL)) == NULL)
	{
		ft_putstr_fd("Error termcaps\n", 2);
		return ;
	}
	while (count > 0)
	{
		if (index == colnbr)
		{
			ret2 = tgetstr("nw", NULL);
			ft_putstr(ret2);
		}
		ft_putstr(ret);
		count--;
	}*/
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
