/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   makepath.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 12:13:18 by tmaraval          #+#    #+#             */
/*   Updated: 2018/05/31 14:53:18 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"

int		make_path_find_last_slash(char *path)
{
	int i;

	i = ft_strlen(path);
	while (i >= 0)
	{
		if (path[i] == '/')
			return (i);
		i--;
	}
	return (0);
}

void	make_path_manage_last_slash(char **path, int flg)
{
	char *tmp;

	if (flg == PATH_ADD_SLASH)
	{
		if (path[0][ft_strlen(*path)] == '/')
			return ;
		else
		{
			tmp = path[0];
			path[0] = ft_strjoin(path[0], "/");
			free(tmp);
		}
	}
	if (flg == PATH_REM_SLASH)
	{
		if (path[0][ft_strlen(path[0])] != '/')
			return ;
		else
			path[0][ft_strlen(path[0])] = '\0';
	}
}

char	*make_path_dotdot(char **curpath, char **dir)
{
	char *tmp;

	if (ft_strcmp(*dir, "../") == 0 || ft_strcmp(*dir, "..") == 0)
	{
		make_path_manage_last_slash(curpath, PATH_REM_SLASH);
		curpath[0][make_path_find_last_slash(*curpath)] = '\0';
		return (*curpath);
	}
	make_path_manage_last_slash(curpath, PATH_REM_SLASH);
	curpath[0][make_path_find_last_slash(*curpath)] = '\0';
	make_path_manage_last_slash(curpath, PATH_ADD_SLASH);
	tmp = *curpath;
	*curpath = ft_strjoin(*curpath, dir[0] + 3);
	free(tmp);
	return (*curpath);
}

char	*make_path_dotslash(char **curpath, char **tmp, char *dir)
{
	make_path_manage_last_slash(curpath, PATH_ADD_SLASH);
	*tmp = *curpath;
	*curpath = ft_strjoin(*curpath, dir + 2);
	free(*tmp);
	return (*curpath);
}

char	*make_path(char *path, char *dir)
{
	char *tmp;
	char *curpath;

	curpath = ft_strdup(path);
	if (dir == NULL || ft_strcmp(dir, "./") == 0 || ft_strcmp(dir, ".") == 0
		|| ft_strlen(dir) == 0)
		return (curpath);
	if (ft_strncmp(dir, "./", 2) == 0)
		return (make_path_dotslash(&curpath, &tmp, dir));
	if (ft_strncmp(dir, "../", 2) == 0)
		return (make_path_dotdot(&curpath, &dir));
	if (dir[0] == '/')
	{
		free(curpath);
		return (ft_strdup(dir));
	}
	make_path_manage_last_slash(&curpath, PATH_ADD_SLASH);
	make_path_manage_last_slash(&dir, PATH_REM_SLASH);
	tmp = curpath;
	curpath = ft_strjoin(curpath, dir);
	free(tmp);
	return (curpath);
}

/*int		main(int argc, char **argv)
{
	char *path;
	
	path =  make_path(argv[1], argv[2]);
	ft_printf("curpath = |%s|\n", argv[1]);
	ft_printf("dir = |%s|\n", argv[2]);
	ft_printf("new curpath |%s|\n", path);
	free(path);
	return (0);
}*/
