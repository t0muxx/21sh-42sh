/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   makepath.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 12:13:18 by tmaraval          #+#    #+#             */
/*   Updated: 2018/10/11 11:57:28 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include <unistd.h>

int		make_path_cnt_slash(char *str)
{
	int i;
	int cnt;

	i = 0;
	cnt = 0;
	while (str[i])
	{
		if (str[i] == '/')
			cnt++;
		i++;
	}
	return (cnt);
}

void	make_path_dotdot(char **retpath)
{
	if (ft_strcmp(retpath[0], "/"))
	{
		if (retpath[0][ft_strlen(retpath[0])] == '/')
			make_path_manage_last_slash(retpath, PATH_REM_SLASH);
		if (make_path_cnt_slash(retpath[0]) != 1)
			retpath[0][make_path_find_last_slash(retpath[0])] = '\0';
		else
			retpath[0][make_path_find_last_slash(retpath[0]) + 1] = '\0';
	}
}

void	make_path_concat(char **retpath, char **dir)
{
	char *tmp;

	if (ft_strlen(retpath[0]) != 0
	&& retpath[0][ft_strlen(retpath[0]) - 1] != '/')
		make_path_manage_last_slash(retpath, PATH_ADD_SLASH);
	if (dir[0][0] == '/')
		make_path_manage_last_slash(dir, PATH_REM_SLASH);
	tmp = retpath[0];
	retpath[0] = ft_strjoin(retpath[0], dir[0]);
	free(tmp);
}

void	make_path_do(char **spliteddir, char **retpath)
{
	if (!ft_strcmp(spliteddir[0], "."))
		NULL;
	else if (!ft_strcmp(spliteddir[0], ".."))
		make_path_dotdot(retpath);
	else
		make_path_concat(retpath, &spliteddir[0]);
}

char	*make_path(char *path, char *dir)
{
	char	**spliteddir;
	char	*retpath;
	int		i;

	i = 0;
	if (dir == NULL || ft_strlen(dir) == 0)
		return (path);
	if (!ft_strcmp(dir, "/"))
		return (retpath = ft_strdup("/"));
	if (!ft_strncmp(dir, "/", 1))
		retpath = ft_strdup("/");
	else
		retpath = ft_strdup(path);
	if (ft_strcmp(retpath, "/"))
		make_path_manage_last_slash(&retpath, PATH_REM_SLASH);
	spliteddir = ft_strsplit(dir, '/');
	while (spliteddir[i])
	{
		make_path_do(&spliteddir[i], &retpath);
		i++;
	}
	utils_free_2darray((void **)spliteddir);
	return (retpath);
}
