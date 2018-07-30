/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 11:13:48 by tmaraval          #+#    #+#             */
/*   Updated: 2018/07/30 14:03:30 by tomux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

int		path_exec(char *cmd, char **arg, char **env)
{
	pid_t	pid;
	int		status;

	if (access(cmd, F_OK) == -1)
		return (EXISTERR);
	if (access(cmd, X_OK) == -1)
		return (PERMERR);
	else
	{
		pid = fork();
		if (pid == -1)
			error_fork_err();
		else if (pid == 0)
		{
			if (execve(cmd, arg, env) == -1)
			{
				exit(EXIT_FAILURE);
				return (EXECVERR);
			}
		}
		else
			waitpid(pid, &status, 0);
	}
	return (0);
}

int		path_exec_in(char *cmd, char **arg, char **env)
{
	char	*execute;
	int		ret;

	if (cmd[0] == '.')
		return (path_exec(cmd, arg, env));
	if (cmd[0] == '/')
		return (path_exec(cmd, arg, env));
	else if ((execute = path_find_in_path(cmd, env)) != NULL)
	{
		ret = path_exec(execute, arg, env);
		free(execute);
		return (ret);
	}
	else
		return (EXISTERR);
}

char	*path_find_in_path(char *name, char **myenv)
{
	char	**patharray;
	char	*path;
	int		i;

	i = 0;
	if (!(path = env_get_var("PATH", myenv)))
		return (NULL);
	patharray = ft_strsplit(path, ':');
	free(path);
	if (name[0] == '/')
		return (name);
	if ((name[0] == '.' && name[1] == '/') ||
	(name[0] == '.' && name[1] == '.' && name[2] == '/'))
	{
		if (access(name, F_OK) == 0 && access(name, X_OK) == 0)
			return (name);
		else if (access(name, F_OK) == 0 && access(name, X_OK) == -2)
		{
			error_print(2, name, "");
			exit(EXIT_FAILURE);
		}
		else if (access(name, F_OK) == -1)
		{
			error_print(3, name, "");
			exit(EXIT_FAILURE);
		}
	}
	while (patharray[i])
	{
		path = utils_makepath(patharray[i], name);
		if (access(path, F_OK) == -1)
			ft_strdel(&path);
		else
			break ;
		i++;
	}
		utils_free_2darray((void **)patharray);
	return (path);
}
