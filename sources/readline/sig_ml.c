/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 14:30:36 by tmaraval          #+#    #+#             */
/*   Updated: 2018/09/12 11:55:54 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include <signal.h>
#include <sys/ioctl.h>
#include "env.h"

t_buffer *g_tbuffer2;
t_buffer *g_mlbuffer2;

void	sig_handler_ml(int sigid)
{
	struct winsize w;

	ioctl(0, TIOCGWINSZ, &w);
	if (sigid == SIGINT)
	{
		cursor_move_right(g_tbuffer2, (int)ft_strlen(g_tbuffer2->buffer));
		tbuffer_init(g_tbuffer2, env_create_copy());
		g_tbuffer2->ctrlc = 1;
		g_mlbuffer2->ctrlc = 1;
		ft_bzero(g_tbuffer2->buffer, (int)ft_strlen(g_tbuffer2->buffer));
		ft_bzero(g_mlbuffer2->buffer, (int)ft_strlen(g_mlbuffer2->buffer));
		close(0);
	}
	if (sigid == SIGWINCH)
	{
		g_tbuffer2->colnbr = w.ws_col;
		line_reset(g_tbuffer2);
	}
}

void	sig_intercept_ml(t_buffer *tbuffer, t_buffer *mlbuffer)
{
	g_tbuffer2 = tbuffer;
	g_mlbuffer2 = mlbuffer;
	signal(SIGINT, sig_handler_ml);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGWINCH, sig_handler_ml);
	tbuffer = g_tbuffer2;
	mlbuffer = g_mlbuffer2;
}
