/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 17:45:57 by tmaraval          #+#    #+#             */
/*   Updated: 2018/03/29 17:53:39 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	insert_char(t_buffer *tbuffer, char *read_buf)
{
	if (tbuffer->buffer[tbuffer->cnt] == 0)
	{
		if (tbuffer->index + tbuffer->prompt_len == tbuffer->colnbr -1)
		{
			line_go_down(1);
			tbuffer->index = 0;
			tbuffer->line++;
		}
		tbuffer->buffer[tbuffer->cnt] = read_buf[0];
		tbuffer->cnt++;
		tbuffer->index++;
		write(1, read_buf, 1);
	}
}
