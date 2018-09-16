/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_chdir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 13:35:47 by tmaraval          #+#    #+#             */
/*   Updated: 2018/09/16 11:52:14 by tomux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"
#include "env.h"

int		cd_err_chdir(char *dir)
{
	if (chdir(dir) == -1)
	{
		if (access(dir, F_OK) == -1)
			error_print(EXISTERR, "cd", dir);
		else if (utils_is_dir(dir) != 1)
			error_print(NOTADIR, "cd", dir);
		else if (access(dir, X_OK) == -1)
			error_print(PERMERR, "cd", dir);
		else
			error_print(UNDEFINEDERR, "cd", dir);
		return (-1);
	}
	return (0);
}

int		cd_change_dir_p(char *oldpwd, char *pwd, char *dir, char ***env)
{
	if (cd_err_chdir(dir) == -1)
	{
		free(oldpwd);
		free(dir);
		return (-1);
	}
	if ((env_update_var("OLDPWD", oldpwd, *env)) == 0)
		*env = env_add_var("OLDPWD", oldpwd, env);
	pwd = getcwd(pwd, PATH_MAX);
	env_update_var("PWD", pwd, *env);
	free(pwd);
	free(oldpwd);
	free(dir);
	return (0);
}

int		cd_change_dir_dash(char *oldpwd, char **dir, char ***env)
{
	char *tmp;

	if (!ft_strcmp("-", *dir))
	{
		tmp = *dir;
		if ((*dir = env_get_var("OLDPWD", *env)) == NULL)
		{
			free(oldpwd);
			error_print(10, "cd", "");
			return (-1);
		}
		ft_printf("%s\n", *dir);
		return (1);
	}
	return (0);
}

int		cd_change_dir_gen(char *oldpwd, char **pwd, char *dir, char ***env)
{
	if (pwd)
		NULL;
	if (cd_err_chdir(dir) == -1)
	{
		free(dir);
		free(oldpwd);
		return (-1);
	}
	if (env_update_var("OLDPWD", oldpwd, *env) == 0)
		*env = env_add_var("OLDPWD", oldpwd, env);
	if (env_update_var("PWD", dir, *env) == 0)
		*env = env_add_var("PWD", dir, env);
	free(dir);
	free(oldpwd);
	return (0);
}
