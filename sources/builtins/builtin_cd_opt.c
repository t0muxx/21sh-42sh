/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_opt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlulu <tomlulu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 16:47:14 by tomlulu           #+#    #+#             */
/*   Updated: 2018/02/02 10:43:45 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		builtin_cd_dooldpwd(char *pwd, t_cd_opt *opt, char **myenv)
{
	char	*oldpwd;
	int		ret;

	ret = 0;
	oldpwd = env_get_var("OLDPWD", myenv);
	if (oldpwd == NULL)
		return (-1);
	ret = builtin_cd_createpath(pwd, oldpwd, opt, myenv);
	free(oldpwd);
	return (ret);
}

int		builtin_cd_cdpath_chdir(char *pwd, char *temppath, char **myenv)
{
	int ret;

	ret = 0;
	if (temppath && ft_strlen(temppath) != 0 &&
	(builtin_cd_dir(temppath, 1) == 0))
	{
		env_update_var("OLDPWD", pwd, myenv);
		getcwd(pwd, PATH_MAX);
		env_update_var("PWD", pwd, myenv);
		return (1);
	}
	else if (ret == -1)
		return (-1);
	else
		return (0);
}

int		builtin_cd_cdpath_test(char *pwd, char *path, char *cdpath,
	char **myenv)
{
	char	**cdpatharray;
	char	*temppath;
	int		i;
	int		ret;

	ret = 0;
	i = 0;
	cdpatharray = ft_strsplit(cdpath, ':');
	while (cdpatharray[i])
	{
		temppath = utils_makepath(cdpatharray[i], path);
		if (access(temppath, F_OK) == -1)
			ft_strdel(&temppath);
		else
			break ;
		i++;
	}
	ret = builtin_cd_cdpath_chdir(pwd, temppath, myenv);
	free(temppath);
	utils_free_2darray((void **)cdpatharray);
	return (ret);
}

int		builtin_cd_cdpath(char *pwd, char *path, char **myenv)
{
	char	*cdpath;
	int		ret;

	ret = 0;
	if ((cdpath = env_get_var("CDPATH", myenv)) != NULL
	&& ft_strcmp("..", path) != 0 && ft_strcmp("~/", path) != 0)
		ret = builtin_cd_cdpath_test(pwd, path, cdpath, myenv);
	free(cdpath);
	return (ret);
}
