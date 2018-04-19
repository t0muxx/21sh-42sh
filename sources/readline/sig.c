/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 14:30:36 by tmaraval          #+#    #+#             */
/*   Updated: 2018/04/19 11:12:56 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include <signal.h>
#include <sys/ioctl.h>

static	t_buffer tbuffer2;

void	sig_handler(int sigid, siginfo_t *siginfo, void *context)
{
	struct winsize w;
	
	ioctl(0, TIOCGWINSZ, &w);
	if (sigid == SIGINT)
	{
		cursor_move_right(&tbuffer2, (int)ft_strlen(tbuffer2.buffer));
		ft_putstr("\n");
		tbuffer_init(&tbuffer2);
		prompt_print(&tbuffer2);
	}	
	if (sigid == SIGWINCH)
	{
		tbuffer2.colnbr = w.ws_col;
		line_reset(&tbuffer2);	
		//ft_printf("|%d|\n", tbuffer2.colnbr);
	}	
	if (siginfo)
		;
	if (context)
		;
}

void	sig_intercept(t_buffer *tbuffer)
{
	struct sigaction sa;

	tbuffer2 = *tbuffer;
	//tbuffer2.cnt = tbuffer->cnt;
	//tbuffer2.index = tbuffer->index;
	//tbuffer2.line = tbuffer->line;
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = sig_handler;
	sa.sa_flags = 0;
	sigemptyset(&(sa.sa_mask));
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGWINCH, &sa, NULL);
	tbuffer2 = *tbuffer;
//	printf("cnt = %d\n", tbuffer2.cnt);
//	printf("index = %d\n", tbuffer2.index);
//	printf("line = %d\n", tbuffer2.line);
}
