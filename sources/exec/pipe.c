/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 03:20:55 by cormarti          #+#    #+#             */
/*   Updated: 2018/06/06 16:41:37 by tmaraval         ###   ########.fr       */
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
		/*if (astree->left->type == NT_CMD )
		{
			cmd = lst_arr(astree->left->arg, env);
			ft_printf("node type = |%d|\n", astree->left->type);
			ft_printf("node cmd = |%s|\n", cmd[0]);
			utils_free_2darray((void **)cmd);
		}
		cmd = lst_arr(astree->right->arg, env);
		ft_printf("node type = |%d|\n", astree->right->type);
		ft_printf("node cmd = |%s|\n", cmd[0]);
		ft_printf("is root = |%d|\n", astree->is_root_node);
		utils_free_2darray((void **)cmd);
	//}*/
	if (astree->is_root_node == 0)
	{
		if (pipe(newfds) == -1)
		{
			ft_printf("Error during pipe\n");
			return (-1);
		}
	}
	if (astree->left->left == NULL && astree->left->type == NT_CMD)
	{
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
				dup2(newfds[1], 1);
				//close(newfds[1]);
			}
			cmd = lst_arr(astree->left->arg, env);
			dprintf(2, "Executing cmd = |%s|\n", cmd[0]);
			if (execve(cmd[0], cmd, env) == -1)
			{
				dprintf(2, "ERROR : Executing cmd = |%s|\n", cmd[0]);
				perror("execve");
			}
			exit(EXIT_SUCCESS);
			utils_free_2darray((void **)cmd);
		}
		else
		{
			waitpid(pid, &status, 0);
			if (astree->right->type == NT_CMD)
			{
				dprintf(2, "pipe following\n");
				exec->oldfds[0] = newfds[0];
				exec->oldfds[1] = newfds[1];
			}
		}
	}
	if ((pid2 = fork()) == -1)
	{
		ft_printf("Error during fork\n");
		return (-1);
	}
	else if (pid2 == 0)
	{
		if (astree->left->type == NT_CMD)
		{
			dup2(exec->oldfds[0], 0);
			//close(exec->oldfds[0]);
			close(exec->oldfds[1]);
		}
		if (astree->is_root_node == 0)
		{
			dprintf(2, "Not Root node !\n");
			close(newfds[0]);
			dup2(newfds[1], 1);
			close(newfds[1]);
		}
		cmd = lst_arr(astree->right->arg, env);
		dprintf(2, "Executing cmd = |%s|\n", cmd[0]);
		if (execve(cmd[0], cmd, env) == -1)
		{
			dprintf(2, "ERROR : Executing cmd = |%s|\n", cmd[0]);
			close(newfds[0]);
			close(newfds[1]);
			close(exec->oldfds[0]);
			close(exec->oldfds[1]);
			perror("execve");
		}
		exit(EXIT_SUCCESS);
		utils_free_2darray((void **)cmd);
	}
	else
	{
		waitpid(pid2, &status, 0);
		if ((astree->left->type == NT_PIPE || astree->left->type == NT_CMD))
		{
			//close(exec->oldfds[0]);
			close(exec->oldfds[1]);
		}
		if (astree->is_root_node == 0)
		{
			exec->oldfds[0] = newfds[0];
			exec->oldfds[1] = newfds[1];
		}
	}
	//close(exec->oldfds[0]);
	//close(exec->oldfds[1]);
	return (0);
}
