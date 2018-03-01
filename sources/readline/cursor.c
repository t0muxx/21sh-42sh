/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 08:17:44 by tmaraval          #+#    #+#             */
/*   Updated: 2018/03/01 11:49:18 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <termcap.h>
#include <term.h>
#include "cursor.h"

void	cursor_delete_line()
{
	char	*temp;
	
	temp = tgetstr("dl", NULL);
	tputs(temp, 0, ft_putcc);
}

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


void	cursor_move_right(int count)
{
	char *temp;
	
	temp = tgetstr("nd", NULL);
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
