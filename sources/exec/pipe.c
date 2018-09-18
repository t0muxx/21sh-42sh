/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 03:20:55 by cormarti          #+#    #+#             */
/*   Updated: 2018/09/18 09:34:07 by tmaraval         ###   ########.fr       */
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
#include "builtin.h"

int		pipeline_exec_cmd(char **cmd, char **env)
{
	char *cmd_path;

	if (cmd)
	{
		cmd_path = path_find_in_path(cmd[0], env);
		execve(cmd_path, cmd, env);
		error_print(CMDNOTFOUND, cmd[0], "");
	}
	exit(EXIT_FAILURE);
	return (1);
}

void	pipeline_exec_child(t_pipeline *pipeline, int pipefd[2],
int read_pipe, char **env)
{
	sig_child();
	if (read_pipe != 0)
	{
		dup2(read_pipe, 0);
		close(read_pipe);
	}
	if (pipeline->next != NULL)
		dup2(pipefd[1], 1);
	close(pipefd[1]);
	close(pipefd[0]);
	if (*(pipeline->cmd) &&
	builtin_check_builtin(pipeline->node, pipeline->cmd, &env) == 1)
		exit(EXIT_SUCCESS);
	exec_cmd(pipeline->node, env);
}

void	pipeline_exec(t_pipeline *pipeline, t_exec *exec,
int read_pipe, char **env)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

	if (pipeline == NULL)
		return ;
	if (pipe(pipefd) == -1)
		return ;
	if ((pid = fork()) == -1)
		return ;
	if (pid == 0)
		pipeline_exec_child(pipeline, pipefd, read_pipe, env);
	else
	{
		sig_father();
		if (read_pipe != 0)
			close(read_pipe);
		close(pipefd[1]);
		pipeline_exec(pipeline->next, exec, pipefd[0], env);
		close(pipefd[0]);
		waitpid(pid, &status, 0);
		if (pipeline->next == NULL)
			exec->status = status;
	}
	return ;
}

int		pipeline_create(t_astree *astree, t_exec *exec)
{
	t_pipeline *new;

	if (astree->left->type == NT_CMD)
	{
		new = pipeline_new(astree->left);
		pipeline_add((&exec->pipeline), new);
	}
	if (astree->left->type == NT_SEMI)
	{
		new = pipeline_new(astree->left->right);
		pipeline_add((&exec->pipeline), new);
	}
	new = pipeline_new(astree->right);
	pipeline_add((&exec->pipeline), new);
	return (0);
}

int		node_pipe(t_astree *astree, char ***env, t_exec *exec)
{
	if (astree->root_pipe == 0)
		return (pipeline_create(astree, exec));
	else
	{
		pipeline_create(astree, exec);
		pipeline_exec(exec->pipeline, exec, 0, *env);
		pipeline_free(exec->pipeline);
		exec->pipeline = NULL;
	}
	return (exit_status(exec->status));
}
