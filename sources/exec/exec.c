/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 21:27:01 by cormarti          #+#    #+#             */
/*   Updated: 2018/07/11 19:44:40 by tomux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/astree.h"
#include "../../includes/exec.h"
#include "builtin.h"

/* voir ce quon fait pour ca pose probleme pour ctrl+d*/

int		exit_status(int status)
{
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 0)
			return (1);
		else
			return (0);
	}
/*
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 11)
			ft_putendl("no such file or directory");
		return (0);
	} */
	// Mieux vaut renvoyer le numero du signal , en plus le sig 11 c'est pour segfault ? ducoup pk no no such file or dir
	else if (WIFSIGNALED(status))
	{
		return (WTERMSIG(status));
	}
	return (0);
}

int		fork_and_exec(t_astree *astree, char **env)
{
	pid_t	pid;
	int		status;

	if ((pid = fork()) == -1)
	{
		ft_putendl("failed to fork");
		exit(0);
	}
	else if (pid == 0)
	{
		exec_cmd(astree, env);
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		return (exit_status(status));
	}
	return (0);
}

int		child_process(t_astree *astree, char **env)
{
	pid_t	pid;
	int		status;
	int		i;
	int		last_exec;
	t_exec exec;
	char		**cmd;
	i = 0;
	last_exec = 0;

	exec.process_pid = NULL;
	cmd = lst_arr(astree->arg);
	if (astree->type == NT_CMD && builtin_check_builtin(cmd, &env) == 1)
		return (0);
	if ((pid = fork()) == -1)
	{
		ft_putendl("failed to fork");
		exit(0);
	}
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (astree->type == NT_CMD)
			exec_cmd(astree, env);
		else
		{
			astree->is_root_node = 1;
			last_exec = exec_node(astree, env, &exec);
		}
		exit(EXIT_SUCCESS);
	}
	else if (pid > 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		waitpid(pid, &status, 0);
		if (exit_status(status) == SIGINT)
			ft_printf("\n");
		t_process_free(exec.process_pid);
	}
	return (0);
}
