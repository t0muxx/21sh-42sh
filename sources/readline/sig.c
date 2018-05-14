/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 14:30:36 by tmaraval          #+#    #+#             */
/*   Updated: 2018/05/14 11:39:39 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include <signal.h>
#include <sys/ioctl.h>
#include "env.h"

static	t_buffer g_tbuffer2;

void	sig_handler(int sigid, siginfo_t *siginfo, void *context)
{
	struct winsize w;

	ioctl(0, TIOCGWINSZ, &w);
	if (sigid == SIGINT)
	{
		cursor_move_right(&g_tbuffer2, (int)ft_strlen(g_tbuffer2.buffer));
		ft_putstr("\n");
		tbuffer_init(&g_tbuffer2, env_create_copy());
		prompt_print(&g_tbuffer2);
	}
	if (sigid == SIGWINCH)
	{
		g_tbuffer2.colnbr = w.ws_col;
		line_reset(&g_tbuffer2);
	}
	if (siginfo)
		;
	if (context)
		;
}

void	sig_intercept(t_buffer *tbuffer)
{
	struct sigaction sa;

	g_tbuffer2 = *tbuffer;
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = sig_handler;
	sa.sa_flags = 0;
	sigemptyset(&(sa.sa_mask));
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGWINCH, &sa, NULL);
	g_tbuffer2 = *tbuffer;
}
