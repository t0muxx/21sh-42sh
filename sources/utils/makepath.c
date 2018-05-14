/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   makepath.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 12:13:18 by tmaraval          #+#    #+#             */
/*   Updated: 2018/04/26 15:13:28 by tmaraval         ###   ########.fr       */
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

char	*make_path(char *curpath, char *dir)
{
	char *tmp;

	if (dir == NULL || ft_strcmp(dir, "./") == 0 || ft_strcmp(dir, ".") == 0
		|| ft_strlen(dir) == 0)
		return (curpath);
	if (ft_strncmp(dir, "./", 2) == 0)
	{
		make_path_manage_last_slash(&curpath, PATH_ADD_SLASH);
		tmp = curpath;
		curpath = ft_strjoin(curpath, dir + 2);
		return (curpath);
	}
	if (ft_strcmp(dir, "../") == 0 || ft_strcmp(dir, "..") == 0)
	{
		make_path_manage_last_slash(&curpath, PATH_REM_SLASH);
		curpath[make_path_find_last_slash(curpath)] = '\0';
		return (curpath);
	}
	if (ft_strncmp(dir, "../", 3) == 0)
	{
		make_path_manage_last_slash(&curpath, PATH_REM_SLASH);
		curpath[make_path_find_last_slash(curpath)] = '\0';
		make_path_manage_last_slash(&curpath, PATH_ADD_SLASH);
		tmp = curpath;
		curpath = ft_strjoin(curpath, dir + 3);
		return (curpath);
	}
	if (dir[0] == '/')
		return (dir);
	make_path_manage_last_slash(&curpath, PATH_ADD_SLASH);
	make_path_manage_last_slash(&dir, PATH_REM_SLASH);
	tmp = curpath;
	curpath = ft_strjoin(curpath, dir);
	free(tmp);
	return (curpath);	
}

/*int		main(int argc, char **argv)
{
	ft_printf("curpath = |%s|\n", argv[1]);
	ft_printf("dir = |%s|\n", argv[2]);
	ft_printf("new curpath |%s|\n", make_path(argv[1], argv[2]));
	return (0);
}*/

