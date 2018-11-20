/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 14:30:36 by tmaraval          #+#    #+#             */
/*   Updated: 2018/11/20 15:08:04 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include <signal.h>
#include <sys/ioctl.h>
#include "env.h"
#include "utils.h"
#include <sys/wait.h>

t_buffer *g_tbuffer2;

void	input_ctrl_d(t_buffer *tbuffer, char *read_buf)
{
	if (read_buf[0] == 4 && ft_strlen(read_buf) == 1 &&
	ft_strlen(tbuffer->buffer) == 0)
	{
		ft_putendl("");
		free(tbuffer->buffer);
		term_close();
		exit(EXIT_SUCCESS);
	}
	else if (read_buf[0] == 4 && ft_strlen(read_buf) == 1 &&
	tbuffer->cnt != (int)ft_strlen(tbuffer->buffer))
	{
		line_reset(tbuffer);
		string_delete_char(&(tbuffer->buffer), tbuffer->cnt);
		cursor_save_pos(tbuffer);
		line_go_begin(tbuffer);
		tbuffer->cnt = 0;
		tbuffer->index = 0;
		tputs(tbuffer->termcap->cd, 0, ft_putcc);
		prompt_print(tbuffer);
		insert_tbuffer(tbuffer);
		cursor_reload_pos(tbuffer);
	}
}

void	sig_handler(int sigid)
{
	struct winsize	w;

	ioctl(0, TIOCGWINSZ, &w);
	if (sigid == SIGINT)
	{
		cursor_move_right(g_tbuffer2, (int)ft_strlen(g_tbuffer2->buffer));
		ft_putstr("\n");
		free(g_tbuffer2->buffer);
		free(g_tbuffer2->termcap);
		tbuffer_init(g_tbuffer2, g_tbuffer2->env);
		prompt_print(g_tbuffer2);
		ft_bzero(g_tbuffer2->buffer, (int)ft_strlen(g_tbuffer2->buffer));
	}
	if (sigid == SIGWINCH)
	{
		g_tbuffer2->colnbr = w.ws_col;
		line_reset(g_tbuffer2);
	}
	if (sigid == SIGTERM)
	{
		if (waitpid(0, NULL, WNOHANG) == -1)
			exit(0);
	}
}

void	sig_intercept(t_buffer *tbuffer)
{
	g_tbuffer2 = tbuffer;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGWINCH, sig_handler);
	signal(SIGTERM, sig_handler);
	tbuffer = g_tbuffer2;
}
