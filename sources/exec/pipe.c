/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 03:20:55 by cormarti          #+#    #+#             */
/*   Updated: 2018/07/24 14:05:53 by tomux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/astree.h"
#include "../../includes/exec.h"
#include "utils.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int			pipe_routine_astree_left(t_astree *astree, char **env,
t_exec *exec, t_process *new)
{
	t_astree	*cmd;
	pid_t		pid;

	if (astree->left->type != NT_PIPE && (cmd = astree->left))
	{
		if (astree->left->type == NT_OR_IF || astree->left->type == NT_AND_IF)
			cmd = astree->left->right;
		if (pipe(exec->newfds) == -1)
			return (pipe_err_pipe());
		if ((pid = fork()) == -1)
			return (pipe_err_fork());
		else if (pid == 0)
		{
			sig_child();
			dup2_routine(exec->newfds[1], 1, exec->newfds[0]);
			exec_cmd(cmd, env);
		}
		else
		{
			sig_father();
			new = t_process_new(pid);
			t_process_add(&(exec->process_pid), new);
			close(exec->newfds[1]);
			cpy_fd_routine(exec->oldfds, exec->newfds);
		}
	}
	return (0);
}

void		pipe_wait_err(int status, t_exec *exec)
{
	int status2;

	if (WEXITSTATUS(status) == EXIT_FAILURE)
	{
		close(exec->oldfds[0]);
		close(exec->oldfds[1]);
		while (exec->process_pid->next != NULL)
		{
	//		kill((pid_t)exec->process_pid, SIGKILL);
			exec->process_pid = exec->process_pid->next;
		}
	//	waitpid((exec->process_pid->pid), &status2, 0);
		exec->err_pipeline = -1;
	}
}

void		pipe_routine_astree_right_pere(t_astree *astree, char **env,
t_exec *exec, t_process *new)
{
	int status;

	new = t_process_new(exec->pid);
	t_process_add(&(exec->process_pid), new);
	if (astree->is_root_node == 0)
	{
		close(exec->newfds[1]);
		cpy_fd_routine(exec->oldfds, exec->newfds);
	}
	else
	{
		close_routine(exec->newfds);
		while (waitpid(-1, &status, 0) > 0)
			pipe_wait_err(status, exec);
		exec->status = status;
		dprintf(2, "|%d|\n", WEXITSTATUS(status));
		close_routine(exec->oldfds);
	}
}

int			pipe_routine(t_astree *astree, char **env, t_exec *exec)
{
	int			newfds[2];
	t_process	*new;

	pipe_routine_astree_left(astree, env, exec, new);
	if (pipe(exec->newfds) == -1)
		return (pipe_err_pipe());
	if ((exec->pid = fork()) == -1)
		return (pipe_err_fork());
	else if (exec->pid == 0)
	{
		sig_child();
		new = t_process_new(getpid());
		t_process_add(&(exec->process_pid), new);
		dup2_routine(exec->oldfds[0], 0, exec->oldfds[1]);
		if (astree->is_root_node == 0)
			dup2_routine(exec->newfds[1], 1, exec->newfds[0]);
		exec_cmd(astree->right, env);
	}
	else
	{
		sig_father();
		pipe_routine_astree_right_pere(astree, env, exec, new);
	}
	return (0);
}

int			node_pipe(t_astree *astree, char **env, t_exec *exec)
{
	pipe_routine(astree, env, exec);
	return (exec->status);
}
