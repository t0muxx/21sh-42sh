/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 14:30:36 by tmaraval          #+#    #+#             */
/*   Updated: 2018/06/23 15:02:24 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include <signal.h>
#include <sys/ioctl.h>
#include "env.h"

static	t_buffer g_tbuffer2;

void	sig_handler(int sigid)
{
	struct winsize w;
	
	//ft_printf("\n\n ekfokeofkoefoef \n\n");
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
	if (sigid == SIGQUIT)
	{
		exit(EXIT_SUCCESS);
	}
}

void	sig_intercept(t_buffer *tbuffer)
{

	g_tbuffer2 = *tbuffer;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGWINCH, sig_handler);
	*tbuffer = g_tbuffer2;
}
