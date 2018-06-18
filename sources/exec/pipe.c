/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 03:20:55 by cormarti          #+#    #+#             */
/*   Updated: 2018/06/18 11:31:25 by tomlulu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/astree.h"
#include "../../includes/exec.h"
#include "../../includes/ext_node_fun.h"
#include "utils.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

void	fd_status(int pipefd[2])
{
	pid_t pid;

	pid = getpid();
	dprintf(2, " ########## fd status ###########\n");
	dprintf(2, "in pid %d\n", pid);
	dprintf(2, "fd[0] = %d\n", pipefd[0]);
	if (fcntl(pipefd[0], F_GETFD) == -1)
	{
		perror("fcntl");
	}
	else
	{
		ft_printf("open\n");
	}
	dprintf(2, "fd[1] = %d\n", pipefd[1]);
	if (fcntl(pipefd[1], F_GETFD) == -1)
	{
		perror("fcntl");
	}
	else
	{
		ft_printf("open\n");
	}
	dprintf(2, "##########################\n");

}

int		node_pipe(t_astree *astree, char **env, int last_exec, t_exec *exec)
{
	int	newfds[2];
	pid_t pid;
	pid_t pid2;
	char	**cmd;
	int status;

	dprintf(2, "############# APPEL NODE PIPE ###########\n");
	if (astree->left->type == NT_CMD)
	{
		if (pipe(newfds) == -1)
		{
			perror("pipe");
			return (-1);
		}
		if ((pid = fork()) == -1)
		{
			perror("fork");
			return (-1);
		}
		else if (pid == 0)
		{
			close(newfds[0]);
			dup2(newfds[1], 1);
			close(newfds[1]);
			cmd = lst_arr(astree->left->arg, env);
			dprintf(2, "executing |%s|\n", cmd[0]);
			execve(cmd[0], cmd, env);
		}
		else
		{
			/* on a forcement une commande qui suit */
			close(newfds[1]);
			exec->oldfds[0] = newfds[0];
			exec->oldfds[1] = newfds[1];
		}
	}
	if (pipe(newfds) == -1)
	{
		perror("pipe");
		return (-1);
	}
	if ((pid2 = fork()) == -1)
	{
		perror("pipe");
		return (-1);
	}
	else if (pid2 == 0)
	{
		/*on a une commande qui precede*/
		/*exec->oldfds[1] a deja ete clos */
		dup2(exec->oldfds[0], 0);
		close(exec->oldfds[0]);
		if (astree->is_root_node == 0)
		{
			close(newfds[0]);
			dup2(newfds[1], 1);
			close(newfds[1]);
		}
		cmd = lst_arr(astree->right->arg, env);
		dprintf(2, "executing |%s|\n", cmd[0]);
		execve(cmd[0], cmd, env);
	}
	else
	{
		if (astree->is_root_node == 0)
		{
			close(newfds[1]);
			exec->oldfds[0] = newfds[0];
			exec->oldfds[1] = newfds[1];
			
		}
		else
		{
			close(newfds[0]);
			close(newfds[1]);
			waitpid(pid2, &status, 0);
			close(exec->oldfds[0]);
			close(exec->oldfds[1]);
		}
	}
	return (0);
}
