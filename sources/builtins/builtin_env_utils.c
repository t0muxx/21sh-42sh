/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 10:58:51 by tmaraval          #+#    #+#             */
/*   Updated: 2018/10/03 18:29:26 by tomux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "builtin.h"
#include "utils.h"
#include "exec.h"
#include <sys/wait.h>

int		builtin_env_do_builtin(char **cmd, char **env)
{
	t_builtin	bltin[6];

	builtin_get_builtin(bltin);
	if (builtin_check_builtin(NULL, cmd, &env) == 1)
		return (1);
	return (0);
}

int		builtin_env_do_ret(int ret, char *cmd)
{
	if (ret == EXISTERR)
	{
		error_print(EXISTERR, "env", cmd);
		return (127);
	}
	if (ret == PERMERR)
	{
		error_print(PERMERR, "env", cmd);
		return (126);
	}
	return (0);
}

int		builtin_env_exec(char **cmd, char **env, char **newenv)
{
	pid_t	pid;
	int		status;
	char	*cmd_path;

	if ((pid = fork()) == -1)
		error_fork_err();
	else if (pid == 0)
	{
		cmd_path = path_find_in_path(cmd[0], env);
		execve(cmd_path, cmd, newenv);
		error_print(CMDNOTFOUND, cmd[0], "");
		exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, &status, 0);
	return (0);
}

int		builtin_env_do(char **cmd, int *i, char **env)
{
	char	**newenv;
	int		ret;

	ret = 0;
	if ((newenv = builtin_env_get_env(cmd, i)) == NULL)
		return (125);
	if (cmd[*i] == NULL)
	{
		env_print(newenv);
		utils_free_2darray((void **)newenv);
		return (0);
	}
	if (builtin_env_do_builtin(cmd + (*i), newenv) == 1)
	{
		utils_free_2darray((void **)newenv);
		return (0);
	}
	builtin_env_exec(cmd + (*i), env, newenv);
	utils_free_2darray((void **)newenv);
	return (builtin_env_do_ret(ret, cmd[*i]));
}
