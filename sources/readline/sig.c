/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 14:30:36 by tmaraval          #+#    #+#             */
/*   Updated: 2018/09/17 18:29:39 by tomux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include <signal.h>
#include <sys/ioctl.h>
#include "env.h"
#include "utils.h"
#include "exec.h"
#include <sys/types.h>
#include <sys/wait.h>

t_buffer	*g_tbuffer2;
t_exec		*g_exec2;

void	input_ctrl_d(t_buffer *tbuffer, char *read_buf)
{
	if (read_buf[0] == 4 && ft_strlen(read_buf) == 1 && tbuffer->cnt == 0)
	{
		free(tbuffer->buffer);
		term_close();
		exit(EXIT_SUCCESS);
	}
}

void	sig_handler(int sigid)
{
	struct winsize	w;
	pid_t pid;

	pid = 0;
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
	if (sigid == SIGKILL || sigid == SIGTERM)
	{
		/*
		while (g_exec2->pids)
		{
			ft_printf("pid |%d|\n", *(int *)g_exec2->pids->content);
			kill(*(pid_t *)g_exec2->pids->content, sigid);
			g_exec2->pids = g_exec2->pids->next;
		}
		exit(sigid); */
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
	tbuffer = g_tbuffer2;
}

void	sig_intercept_exec(t_exec *exec)
{
	g_exec2 = exec;
	signal(SIGKILL, sig_handler);
	signal(SIGTERM, sig_handler);

}
