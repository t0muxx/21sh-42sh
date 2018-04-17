/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 14:30:36 by tmaraval          #+#    #+#             */
/*   Updated: 2018/04/17 19:18:59 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include <signal.h>

static	t_buffer tbuffer2;

void	sig_handler(int sigid, siginfo_t *siginfo, void *context)
{
	if (sigid == SIGINT)
		exit(0);
	if (sigid == SIGWINCH)
	{
		line_reset(&tbuffer2);	
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
