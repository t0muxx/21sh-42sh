/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_arrow_mline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 15:57:53 by tmaraval          #+#    #+#             */
/*   Updated: 2018/09/12 14:10:25 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "utils.h"

void	input_enter_mline(t_buffer *tbuffer, char *read_buf)
{
	int last;

	if (read_buf[0] == '\n')
	{
		if ((last = ft_strlen(tbuffer->buffer)) > 0)
		{
			if (tbuffer->buffer[last - 1] != '\\')
				ft_strcat(tbuffer->buffer, "\n");
		}
		cursor_move_right(tbuffer, (int)ft_strlen(tbuffer->buffer));
		tbuffer->state = READ_PROCESS;
	}
}
