/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 13:57:04 by tmaraval          #+#    #+#             */
/*   Updated: 2018/05/14 18:23:58 by tmaraval         ###   ########.fr       */
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
		if (dir[0] != '/')
			dir = make_path(pwd, dir);
		if (cd_err_chdir(dir) == -1)
			return (-1);
		env_update_var("OLDPWD", oldpwd, *env);
		env_update_var("PWD", dir, *env);
	}
	return (0);
}

int		builtin_cd(char **cmd, char ***env)
{
	return (0);
}

