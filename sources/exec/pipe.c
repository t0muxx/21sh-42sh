/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 03:20:55 by cormarti          #+#    #+#             */
/*   Updated: 2018/06/11 16:41:23 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/astree.h"
#include "../../includes/exec.h"
#include "../../includes/ext_node_fun.h"
#include "utils.h"

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
	}
	if (astree->left->left == NULL && astree->left->type == NT_CMD)
	{
		dprintf(2, "############# APPEL POUR ASTREE->LEFT ###########\n");
		if ((pid = fork()) == -1)
		{
			ft_printf("Error during fork\n");
			return (-1);
		}
		else if (pid == 0)
		{
			if (astree->right->type == NT_CMD)
			{
				dprintf(2, "On a un pipe qui suit\n");
				close(newfds[0]);
				dup2(newfds[1], STDOUT_FILENO);
				close(newfds[1]);
			}
			cmd = lst_arr(astree->left->arg, env);
			dprintf(2, "Executing cmd = |%s|\n", cmd[0]);
			if ((execve(cmd[0], cmd, env)) == -1)
			{
				dprintf(2, "ERROR : Executing cmd = |%s|\n", cmd[0]);
				perror("execve");
			}
			utils_free_2darray((void **)cmd);
		}
		else
		{
			close(newfds[1]);
			waitpid(pid, &status, 0);
			if (astree->right->type == NT_CMD)
			{
				dprintf(2, "pipe following\n");
				exec->oldfds[0] = newfds[0];
				exec->oldfds[1] = newfds[1];
				printf("pipefd[0] = %d\n", exec->oldfds[0]);
				printf("pipefd[1] = %d\n", exec->oldfds[1]);
			}
		}
	}
	dprintf(2, "############# APPEL POUR ASTREE->RIGHT ###########\n");
	pipe(newfds);
	if ((pid2 = fork()) == -1)
	{
		ft_printf("Error during fork\n");
		return (-1);
	}
	else if (pid2 == 0)
	{
		if (astree->left->type == NT_CMD || astree->left->type == NT_PIPE)
		{
			dprintf(2, "Il ya un pipe avant\n");
			printf("pipefd[0] = %d\n", exec->oldfds[0]);
			printf("pipefd[1] = %d\n", exec->oldfds[1]);
			dup2(exec->oldfds[0], 0);
			close(exec->oldfds[0]);
			close(exec->oldfds[1]);
		}
		if (astree->is_root_node == 0)
		{
			dprintf(2, "Not Root node !\nOn pipe stdout dans newfds[1]\n");
			close(newfds[0]);
			dup2(newfds[1], 1);
			close(newfds[1]);
		}
		cmd = lst_arr(astree->right->arg, env);
		dprintf(2, "Executing cmd = |%s|\n", cmd[0]);
		if (astree->left->type == NT_PIPE)
		{
			int i = 0;
			char c = 0;
				close(exec->oldfds[1]);
				close(newfds[1]);
			while (i < 50)
			{
				printf("i");
				read(exec->oldfds[0], &c, 1);
				printf("%c", c);
				i++;
			}
			exit(EXIT_SUCCESS);
		}
		else
		{
		if (execve(cmd[0], cmd, env) == -1)
		{
			dprintf(2, "ERROR : Executing cmd = |%s|\n", cmd[0]);
			perror("execve");
			exit(EXIT_FAILURE);
		}
		}
		utils_free_2darray((void **)cmd);
	}
	else
	{
		waitpid(pid2, &status, 0);
		if (astree->is_root_node == 0)
		{
			dprintf(2, "Il reste des pipes\n");
			exec->oldfds[0] = newfds[0];
			exec->oldfds[1] = newfds[1];
			printf("pipefd[0] = %d\n", exec->oldfds[0]);
			printf("pipefd[1] = %d\n", exec->oldfds[1]);
		}
	}
//	close(exec->oldfds[0]);
//	close(exec->oldfds[1]);
	return (0);
}
