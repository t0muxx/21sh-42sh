/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_arrow_mline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 15:57:53 by tmaraval          #+#    #+#             */
/*   Updated: 2018/08/21 10:30:50 by tomux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "utils.h"

void	input_enter_mline(t_buffer *tbuffer, char *read_buf)
{
	char *line;

	if (read_buf[0] == '\n')
	{
		ft_strcat(tbuffer->buffer, "\n");
		cursor_move_right(tbuffer, (int)ft_strlen(tbuffer->buffer));
		tbuffer->state = READ_PROCESS;
	}
}
