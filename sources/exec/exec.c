/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 21:27:01 by cormarti          #+#    #+#             */
/*   Updated: 2018/07/25 14:01:04 by tomux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/astree.h"
#include "../../includes/exec.h"
#include "builtin.h"
#include "utils.h"
#include <sys/types.h>
#include <sys/wait.h>

/* voir ce quon fait pour ca pose probleme pour ctrl+d*/

/* EXIT STATUS 0 (EXIT_SUCCESS) si aucun probleme
 * 1 (EXIT_FAILURE) si erreur
 * > 1 si signaux 
 * */

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

int		fork_and_exec(t_astree *astree, char **env)
{
	pid_t	pid;
	int		status;
	char		**cmd;

	cmd = lst_arr(astree->arg);
	if (*cmd && astree->type == NT_CMD && builtin_check_builtin(cmd, &env) == 1)
	{
		utils_free_2darray((void **)cmd);
		return (0);
	}
	utils_free_2darray((void **)cmd);
	if ((pid = fork()) == -1)
	{
		ft_putendl("failed to fork");
		exit(0);
	}
	else if (pid == 0)
	{
		sig_child();
		exec_cmd(astree, env);
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		sig_father();
		waitpid(pid, &status, 0);
		return (exit_status(status));
	}
	return (0);
}

int		child_process(t_astree *astree, char **env)
{
	pid_t	pid;
	int		last_exec;
	t_exec exec;
	int		status;

	last_exec = 0;
	exec.pipeline = NULL;
	exec.parent = 0;
	exec.prec_exec = 0;
	astree->is_root_node = 0;
	if (astree->type == NT_CMD)
		exec.last_exec = fork_and_exec(astree, env);
	else
	{
		if (astree->type == NT_PIPE)
			astree->is_root_node = 1;
		exec.last_exec = exec_node(astree, env, &exec);
	}
	if (exec.last_exec == SIGINT || exec.last_exec == SIGKILL)
		ft_putstr("\n");
	//ft_printf("last_exec |%d|\n", exec.last_exec);
	return (0);
}
