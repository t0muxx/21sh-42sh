/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 21:27:01 by cormarti          #+#    #+#             */
/*   Updated: 2018/09/17 18:15:15 by tomux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/astree.h"
#include "../../includes/exec.h"
#include "builtin.h"
#include "utils.h"
#include <sys/types.h>
#include <sys/wait.h>

/*
** EXIT STATUS 0 (EXIT_SUCCESS) si aucun probleme
** 1 (EXIT_FAILURE) si erreur
** > 1 si signaux
**
*/

void		pids_add(t_exec *exec, pid_t pid)
{
	t_list *new;

	new = ft_lstnew((void *)&pid, sizeof(pid_t));
	ft_lstadd(&(exec->pids), new);
}

int		exit_status(int status)
{
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == EXIT_SUCCESS)
			return (EXIT_SUCCESS);
		else
			return (EXIT_FAILURE);
	}
	else if (WIFSIGNALED(status))
	{
		return (WTERMSIG(status));
	}
	return (0);
}

int		check_builtin(t_astree *astree, char ***env)
{
	char	**cmd;

	cmd = lst_arr(astree->arg);	
	if (*cmd && astree->type == NT_CMD
	&& builtin_check_builtin(astree, cmd, env) == 1)
	{
		utils_free_2darray((void **)cmd);
		return (EXIT_SUCCESS);
	}
	utils_free_2darray((void **)cmd);
	return (EXIT_FAILURE);
}

int		fork_and_exec(t_astree *astree, char ***env, t_exec *exec)
{
	pid_t	pid;
	int		status;

	if (check_builtin(astree, env) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	if ((pid = fork()) == -1)
	{
		ft_putendl("failed to fork");
		return (0);
	}
	else if (pid == 0)
	{
		sig_child();
		exec_cmd(astree, *env);
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		sig_father();
		pids_add(exec, pid);
		waitpid(pid, &status, 0);
		return (exit_status(status));
	}
	return (0);
}

int		child_process(t_astree *astree, char ***env)
{
	t_exec	exec;

	exec.pipeline = NULL;
	exec.parent = 0;
	exec.dont = 0;
	exec.prec_exec = -2;
	exec.pids = NULL;
	astree->is_root_node = 0;
	sig_intercept_exec(&exec);
	if (astree->type == NT_CMD)
		exec.last_exec = fork_and_exec(astree, env, &exec);
	else
	{
		if (astree->type == NT_PIPE)
			astree->is_root_node = 1;
		exec.last_exec = exec_node(astree, env, &exec);
	}
	if (exec.last_exec == SIGINT || exec.last_exec == SIGKILL)
		ft_putstr("\n");
	return (exec.last_exec);
}
