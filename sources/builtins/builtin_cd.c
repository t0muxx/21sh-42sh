/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 13:57:04 by tmaraval          #+#    #+#             */
/*   Updated: 2018/05/15 17:18:54 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"
#include "utils.h"
#include "env.h"
#include "utils.h"

int		cd_err_chdir(char *dir)
{
	if (chdir(dir) == -1)
	{
		if (access(dir, F_OK) == -1)
			error_print(EXISTERR, "cd", dir);
		else if (access(dir, X_OK) == -1)
	        error_print(PERMERR, "cd", dir);
		else
			error_print(UNDEFINEDERR, "cd", dir);
			return (-1);
	}
	return (0);
}

int		cd_change_dir(char *dir, char ***env, int opt)
{
	char *oldpwd;
	char *pwd;

	oldpwd = env_get_var("PWD", *env);
	pwd = env_get_var("PWD", *env);
	if (opt == CD_P)
	{
		if (cd_err_chdir(dir) == -1)
			return (-1);
		env_update_var("OLDPWD", oldpwd, *env);
		pwd = getcwd(pwd, PATH_MAX);
		env_update_var("PWD", pwd, *env);
	}
	else
	{
		if (!ft_strcmp("-", dir))
		{
			dir = oldpwd;
			oldpwd = pwd;
		}
		if (dir[0] != '/')
			dir = make_path(pwd, dir);
		if (cd_err_chdir(dir) == -1)
			return (-1);
		env_update_var("OLDPWD", oldpwd, *env);
		env_update_var("PWD", dir, *env);
	}
	return (0);
}

char		*cd_manage_cdpath(char *dir, char ***env)
{
	char 	*tmp;
	char 	**cdpath;
	int		i;

	i = 0;
	tmp = env_get_var("CDPATH", *env);
	if (tmp == NULL)
		return (NULL);
	cdpath = ft_strsplit(tmp, ';');
	free(tmp);
	while (cdpath[i])
	{
		if (ft_strlen(cdpath[i]) == 0 || cdpath == NULL)
		{
			tmp = ft_strjoin("./", dir);
			if (access(tmp, F_OK) != -1)
				break;
			free(tmp);
		}
		else
		{
			tmp = make_path(cdpath[i], dir);
			if (access(tmp, F_OK) != -1)
				break;
			free(tmp);
		}
	}
	utils_free_2darray((void **)cdpath);
	return (NULL);
}

int		cd_manage_home(char ***env, int opt)
{
	char *tmp;

	tmp = env_get_var("HOME", *env);
	if (tmp == NULL)
	{
		error_print(4, "cd", "");
		return (-1);
	}
	if (cd_change_dir(tmp, env, opt) == -1)
		return (-1);
	return (0);
}

int		builtin_cd(char **cmd, char ***env)
{
	int opt;
	char *dir;
	char *tmp;

	opt = cd_parse_opt(cmd);
	dir = cmd[cd_skip_opt(cmd)];
	if (dir == NULL || ft_strlen(dir) == 0)
	{
		if (cd_manage_home(env, opt) == -1)
				return (-1);
		else
			return (0);
	}
	if (dir[0] == '/')
		return (cd_change_dir(dir, env, opt));
	if ((!ft_strncmp(dir, "..", 2)) || (!ft_strncmp(dir, ".", 1)))
		return (cd_change_dir(dir, env, opt));
	if ((tmp = cd_manage_cdpath(dir, env)) != NULL)
		return (cd_change_dir(tmp, env, opt));
	cd_change_dir(dir, env, opt);
	return (0);
}

