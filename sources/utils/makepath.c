/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   makepath.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 12:13:18 by tmaraval          #+#    #+#             */
/*   Updated: 2018/09/07 11:01:02 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include <unistd.h>

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

int	main(int argc, char **argv)
{
	char *ret;
	char buf[PATH_MAX];

	getcwd(buf, PATH_MAX);
	ret = make_path(buf, argv[1]);
	ft_printf("buf = |%s|\n", buf); 
	ft_printf("ret = |%s|\n", ret); 
}
