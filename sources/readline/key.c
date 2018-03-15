/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 09:20:02 by tmaraval          #+#    #+#             */
/*   Updated: 2018/03/15 09:24:25 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key.h"
#include "cursor.h"
#include <term.h>

void	key_do_arrow(t_buffer *tbuffer, t_cmd_hist *head)
{
	if (tbuffer->c_buf == 'A')
		readline_history_print(&head, head->oldest, tbuffer);
	if (tbuffer->c_buf == 'B')
		readline_history_print(&head, head->newest, tbuffer);
	if (tbuffer->c_buf == 'C')
	{
		if (tbuffer->cnt < (int)ft_strlen(tbuffer->buffer))
			cursor_move_right_upd_tbuffer(1, tbuffer);
	}
		if (tbuffer->c_buf == 'D')
	{
		if (tbuffer->cnt > 0)
			cursor_move_left_upd_tbuffer(1, tbuffer);
	}
}
