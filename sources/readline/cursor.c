/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 08:17:44 by tmaraval          #+#    #+#             */
/*   Updated: 2018/02/23 16:53:36 by tmaraval         ###   ########.fr       */
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

void	cursor_move_left(int count, t_buffer *tbuffer)
{
	char *temp;

	if (tbuffer->cnt != 0 && tbuffer->index == 1)
	{
		tbuffer->line--;
		if (tbuffer->line == 1)
			tbuffer->colnbr -= 3;
		tbuffer->index = tbuffer->colnbr;
	}
	tbuffer->index--;
	ft_putstr("\033[");
	temp = ft_itoa(count);
	ft_putstr(temp);
	ft_putstr("D");
	free(temp);
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
		//ft_printf("?");
		ft_putstr("\033E");
		tbuffer->index = 0;
		tbuffer->line++;
		if (tbuffer->line == 2)
			tbuffer->colnbr += 3;
	}
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
