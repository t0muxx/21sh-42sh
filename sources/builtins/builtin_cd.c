/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 13:57:04 by tmaraval          #+#    #+#             */
/*   Updated: 2018/09/19 19:02:18 by tomux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"
#include "env.h"
#include "utils.h"

int			cd_change_dir(char *dir, char ***env, int opt)
{
	char	*oldpwd;
	char	*pwd;
	char	*tochdir;

	pwd = NULL;
	if ((oldpwd = env_get_var("PWD", *env)) == NULL)
		oldpwd = ft_strdup("");
	if (opt == CD_P)
	{
		tochdir = make_path(oldpwd, dir);
		if (cd_change_dir_p(oldpwd, pwd, tochdir, env) == -1)
			return (-1);
	}
	else
	{
		if (cd_change_dir_dash_or_dir(&dir, &oldpwd, &pwd, env) == -1)
			return (-1);
	}
	return (0);
}

char		*cd_manage_cdpath_do(char *cdpath, char *dir)
{
	char *tmp;

	if (ft_strlen(cdpath) == 0 || cdpath == NULL)
	{
		tmp = ft_strjoin("./", dir);
		if (access(tmp, F_OK) != -1)
		{
			return (tmp);
		}
	}
	else
	{
		tmp = make_path(cdpath, dir);
		if (access(tmp, F_OK) != -1)
		{
			ft_printf("%s\n", tmp);
			return (tmp);
		}
	}
	free(tmp);
	return (NULL);
}

char		*cd_manage_cdpath(char *dir, char ***env)
{
	char	*tmp;
	char	**cdpath;
	int		i;

	i = 0;
	tmp = env_get_var("CDPATH", *env);
	if (tmp == NULL)
		return (NULL);
	cdpath = ft_strsplit(tmp, ';');
	free(tmp);
	while (cdpath[i])
	{
		if ((tmp = cd_manage_cdpath_do(cdpath[i], dir)) != NULL)
		{
			utils_free_2darray((void **)cdpath);
			return (tmp);
		}
		i++;
	}
	utils_free_2darray((void **)cdpath);
	return (NULL);
}

int			cd_manage_home(char ***env, int opt)
{
	char *tmp;

	tmp = env_get_var("HOME", *env);
	if (tmp == NULL)
	{
		error_print(4, "cd", "");
		return (-1);
	}
	if (cd_change_dir(tmp, env, opt) == -1)
	{
		free(tmp);
		return (-1);
	}
	free(tmp);
	return (0);
}

int			builtin_cd(char **cmd, char ***env)
{
	int		opt;
	char	*dir;
	char	*tmp;

	opt = cd_parse_opt(cmd);
	dir = cmd[cd_skip_opt(cmd)];
	if (dir == NULL || ft_strlen(dir) == 0 || !ft_strcmp(dir, "~/"))
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
	{
		cd_change_dir(tmp, env, opt);
		free(tmp);
		return (0);
	}
	cd_change_dir(dir, env, opt);
	return (0);
}
