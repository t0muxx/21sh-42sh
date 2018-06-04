/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 21:27:01 by cormarti          #+#    #+#             */
/*   Updated: 2018/06/04 18:03:07 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/astree.h"
#include "../../includes/exec.h"

int     exit_status(int status)
{
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 0)
			return (1);
		else
			return (0);
	}
	else if (WIFSIGNALED(status))
	{
		ft_putendl("process terminated due to a signal");
		return (0);
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

	exec.stdinput = -1;
	exec.stdoutput = -1;
	exec.stderror = -1;
	exec.executed = 0;
	i = 0;
	last_exec = 0;
	if ((pid = fork()) == -1)
	{
		ft_putendl("failed to fork");
		exit(0);
	}
	else if (pid == 0)
	{
		if (astree->type == NT_CMD)
			exec_cmd(astree, env);
		else
		{
			last_exec = exec_node(astree, env, &exec);
			while (node_fun[i].type)
			{
				if (node_fun[i].type == astree->type)
					node_fun[i].fun(astree->right, env, last_exec, &exec);
				i++;
			}
		}
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
	}
	return (0);
}
