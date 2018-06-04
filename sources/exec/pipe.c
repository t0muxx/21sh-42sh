/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 03:20:55 by cormarti          #+#    #+#             */
/*   Updated: 2018/06/04 19:35:34 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/astree.h"
#include "../../includes/exec.h"
#include "../../includes/ext_node_fun.h"
#include "utils.h"

int		node_pipe(t_astree *astree, char **env, int last_exec, t_exec *exec)
{
	int	pipefd[2];
	int	pipefd2[2];
	pid_t pid;
	char	**cmd;

	ft_printf("Pipe detected\n");
	if (pipe(pipefd) == -1)
	{
		ft_printf("error during pipe\n");
		return (-1);
	}
	if (astree->left->type == NT_CMD)
	{
		cmd = lst_arr(astree->left->arg, env);
		dup2(pipefd[1], STDOUT_FILENO);
		if ((pid = fork()) == -1)
		{
			ft_printf("Error during fork\n");
			return (-1);
		}
		if (pid == 0)
		{
			//close(pipefd[0]);
			ft_printf("executing cmd |%s|\n", cmd[0]);
			execve(cmd[0], cmd, env);
			exit(EXIT_SUCCESS);
		}
		else
		{
			wait(NULL);
			if (exec->parent == NT_PIPE)
			{
				if (pipe(pipefd2) == -1)
				{
					ft_printf("error during pipe\n");
					return (-1);
				}
				ft_printf("Parent node == PIPE\n");
				dup2(pipefd2[1], 0);
				exec->stdinput = pipefd[0];
			}
			utils_free_2darray((void **)cmd);
			dup2(pipefd[0], STDIN_FILENO);
			cmd = lst_arr(astree->right->arg, env);
			ft_printf("executing cmd |%s|\n", cmd[0]);
			execve(cmd[0], cmd, env);
			return (0);
		}
	}
	else
	{
		if (exec->stdinput != -1)
		{
			dup2(exec->stdinput, 1);
			utils_free_2darray((void **)cmd);
			cmd = lst_arr(astree->right->arg, env);
			execve(cmd[0], cmd, env);
		}
	}
	return (0);
}
