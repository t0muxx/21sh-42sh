/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 17:59:22 by tmaraval          #+#    #+#             */
/*   Updated: 2018/07/10 08:48:48 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	line_reset(t_buffer *tbuffer)
{
	if (tbuffer->state == READ_NORMAL)
	{
		cursor_save_pos(tbuffer);
		line_go_begin(tbuffer);
		tputs(tbuffer->termcap->cd, 0, ft_putcc);
		tbuffer->cnt = 0;
		tbuffer->index = 0;
		prompt_print(tbuffer);
		insert_tbuffer(tbuffer);
		cursor_reload_pos(tbuffer);
		tbuffer->cutstart = 0;
		tbuffer->cutend = 0;
	}
}

void	line_go_down(t_buffer *tbuffer, int cnt)
{
	while (cnt)
	{
		tputs(tbuffer->termcap->sf, 0, ft_putcc);
		tbuffer->index = 0;
		tbuffer->line++;
		if (tbuffer->line == 1)
			tbuffer->prompt_len = 3;
		else if (tbuffer->state == READ_IN_QUOTE)
			tbuffer->prompt_len = 2;
		else if (tbuffer->line > 1)
			tbuffer->prompt_len = 0;
		cnt--;
	}
}

void	line_go_begin(t_buffer *tbuffer)
{
	int i;
	int j;

	j = tbuffer->index + tbuffer->prompt_len;
	i = tbuffer->line;
	while (i > 1)
	{
		tputs(tbuffer->termcap->up, 0, ft_putcc);
		tbuffer->line--;
		i--;
	}
	if (tbuffer->line == 1)
	{
		while (j > 0)
		{
			tputs(tbuffer->termcap->le, 0, ft_putcc);
			j--;
		}
		tbuffer->prompt_len = 3;
	}
}

void	line_go_end(t_buffer *tbuffer)
{
	int j;

	j = 0;
	while (j <= tbuffer->colnbr)
	{
		tputs(tbuffer->termcap->nd, 0, ft_putcc);
		j++;
	}
	tbuffer->index = tbuffer->colnbr - tbuffer->prompt_len;
}
