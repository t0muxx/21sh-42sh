/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 09:44:11 by tmaraval          #+#    #+#             */
/*   Updated: 2018/09/20 11:44:35 by tomux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "cursor.h"
#include <term.h>

void			history_print_reset(t_buffer *tbuffer)
{
	char			*cmd;

	line_go_begin(tbuffer);
	tbuffer->cnt = 0;
	tbuffer->index = 0;
	tputs(tbuffer->termcap->cd, 0, ft_putcc);
	prompt_print(tbuffer);
	ft_bzero(tbuffer->buffer, BUFFER_SIZE);
	cmd = ft_strdup("");
	ft_memcpy(tbuffer->buffer, cmd, ft_strlen(cmd));
	insert_tbuffer(tbuffer);
	free(cmd);
}

void			history_print(t_buffer *tbuffer, t_cmd_hist **toprint)
{
	char			*cmd;

	line_go_begin(tbuffer);
	tbuffer->cnt = 0;
	tbuffer->index = 0;
	tputs(tbuffer->termcap->cd, 0, ft_putcc);
	prompt_print(tbuffer);
	if (toprint && (*toprint) != NULL)
	{
		ft_bzero(tbuffer->buffer, BUFFER_SIZE);
		cmd = ft_strdup((*toprint)->cmd);
		if (ft_strlen(cmd) <= BUFFER_SIZE)
			ft_memcpy(tbuffer->buffer, cmd, ft_strlen(cmd));
		else
		{
			ft_putendl_fd("\nError : history cmd too long", 2);
			prompt_print(tbuffer);
		}
		insert_tbuffer(tbuffer);
		free(cmd);
	}
}
