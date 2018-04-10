/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 14:30:36 by tmaraval          #+#    #+#             */
/*   Updated: 2018/04/10 15:53:09 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include <signal.h>

void	sig_handler(int sigid, siginfo_t *siginfo, void *context)
{
	t_buffer *tbuffer;

	tbuffer = (t_buffer *)context;
	if (sigid == SIGINT)
		exit(0);
	if (sigid == SIGWINCH)
	{
		tputs(tgetstr("le", NULL), 0,ft_putcc);
		tputs(tgetstr("nd", NULL), 0,ft_putcc);
	}	
	if (siginfo)
		;
	if (context)
		;
}

void	sig_intercept(t_buffer *tbuffer)
{
	struct sigaction sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = sig_handler;
	sa.sa_flags = 0;
	sigemptyset(&(sa.sa_mask));
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGWINCH, &sa, NULL);
}
