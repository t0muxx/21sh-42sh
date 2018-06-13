/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 03:20:55 by cormarti          #+#    #+#             */
/*   Updated: 2018/06/13 15:05:27 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/astree.h"
#include "../../includes/exec.h"
#include "../../includes/ext_node_fun.h"
#include "utils.h"
#include <fcntl.h>

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
	if (astree->is_root_node != 1 || astree->left->type != NT_PIPE)
	{
		ft_printf("not a root node\n");
		if (pipe(newfds) != 0)
		{
			ft_printf("Error during pipe\n");
			return (-1);
		}
		dprintf(2, "newfds : \n");
		fd_status(newfds);
	}
	if (astree->left->left == NULL && astree->left->type == NT_CMD)
	{
		dprintf(2, "############# APPEL POUR ASTREE->LEFT ###########\n");
	//	fd_status(newfds);
		if ((pid = fork()) == -1)
		{
			ft_printf("Error during fork\n");
			return (-1);
		}
		else if (pid == 0)
		{
			dprintf(2, "#### CHILD FOR ASTREE->LEFT ####\n");
			if (astree->right->type == NT_CMD)
			{
				dprintf(2, "On a un pipe qui suit\n");
				dprintf(2, "On link newfds[1] a stdout et on close le reste\n");
				close(newfds[0]);
				dup2(newfds[1], STDOUT_FILENO);
				close(newfds[1]);
				fd_status(newfds);
			}
			cmd = lst_arr(astree->left->arg, env);
			dprintf(2, "Executing cmd = |%s|\n", cmd[0]);
			if ((execve(cmd[0], cmd, env)) == -1)
			{
				dprintf(2, "ERROR : Executing cmd = |%s|\n", cmd[0]);
				perror("execve");
			}
			dprintf(2, "#### END CHILD ASTREE->LEFT ####\n");
			utils_free_2darray((void **)cmd);
		}
		else
		{
			dprintf(2, "Parent in astree->left\n");
			//waitpid(pid, &status, 0);
			if (astree->right->type == NT_CMD)
			{
				dprintf(2, "pipe following\n");
				dprintf(2, "exec->oldfds = newfds\n");
				fd_status(newfds);
				exec->oldfds[0] = newfds[0];
				exec->oldfds[1] = newfds[1];
			//	printf("pipefd[0] = %d\n", exec->oldfds[0]);
			//	printf("pipefd[1] = %d\n", exec->oldfds[1]);
			}
		}
	}
	dprintf(2, "############# APPEL POUR ASTREE->RIGHT ###########\n");
	pipe(newfds);
	dprintf(2, "creation du newfds\n");
	fd_status(newfds);
	dprintf(2, "oldfds : \n");
	fd_status(exec->oldfds);
	//printf("newfdspipe[0] astree->right = %d\n", newfds[0]);
	//printf("newfdspipe[1] astree->right = %d\n", newfds[1]);
	close(exec->oldfds[1]);
	if ((pid2 = fork()) == -1)
	{
		ft_printf("Error during fork\n");
		return (-1);
	}
	else if (pid2 == 0)
	{
		dprintf(2, "#### CHILD FOR ASTREE->RIGHT ####\n");
		if (astree->left->type == NT_CMD || astree->left->type == NT_PIPE)
		{
			dprintf(2, "Il ya un pipe avant\n");
			fd_status(exec->oldfds);
			dprintf(2, "On link oldfds[0] a stdin et on close le reste\n");
			//printf("pipefd[0] = %d\n", exec->oldfds[0]);
			//printf("pipefd[1] = %d\n", exec->oldfds[1]);
			close(exec->oldfds[1]);
			dup2(exec->oldfds[0], 0);
			close(exec->oldfds[0]);
			fd_status(exec->oldfds);
		}
		if (astree->is_root_node == 0)
		{
			dprintf(2, "Not Root node !\nOn pipe stdout dans newfds[1]\n");
			close(newfds[0]);
			dup2(newfds[1], 1);
			close(newfds[1]);
			//fd_status(newfds);
		}
		cmd = lst_arr(astree->right->arg, env);
		dprintf(2, "Executing cmd = |%s|\n", cmd[0]);
		if (execve(cmd[0], cmd, env) == -1)
		{
			dprintf(2, "ERROR : Executing cmd = |%s|\n", cmd[0]);
			perror("execve");
			exit(EXIT_FAILURE);
		}
		dprintf(2, "#### END CHILD ASTREE->LEFT ####\n");
	}
	else
	{
		dprintf(2, "Parent astree->right\n");
		close(exec->oldfds[0]);
		close(exec->oldfds[1]);
		fd_status(exec->oldfds);
		if (astree->is_root_node == 0)
		{
			//fd_status(exec->oldfds);
			dprintf(2, "Il reste des pipes\n");
			//printf("pipefd[0] = %d\n", exec->oldfds[0]);
			//printf("pipefd[1] = %d\n", exec->oldfds[1]);
			//fd_status(exec->oldfds);
			exec->oldfds[0] = newfds[0];
			exec->oldfds[1] = newfds[1];
			//printf("pipefd[0] = %d\n", exec->oldfds[0]);
			//printf("pipefd[1] = %d\n", exec->oldfds[1]);
		}
		else
		{
			//waitpid(pid2, &status, 0);
			wait(NULL);
			dprintf(2, "on close oldfds\n");
		}
	}
//	close(exec->oldfds[0]);
//	close(exec->oldfds[1]);
	return (0);
}
