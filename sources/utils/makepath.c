/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   makepath.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 12:13:18 by tmaraval          #+#    #+#             */
/*   Updated: 2018/09/07 15:42:34 by tmaraval         ###   ########.fr       */
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
		if (path[0][ft_strlen(*path) - 1] == '/')
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
		if (path[0][ft_strlen(path[0]) - 1] != '/')
			return ;
		else
			path[0][ft_strlen(path[0]) - 1] = '\0';
	}
}

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
	//	printf("|%c|\n", retpath[0][make_path_find_last_slash(retpath[0])]);
//		ft_printf("retpath |%s|\n", retpath[0]);
		if (make_path_cnt_slash(retpath[0]) != 1)
			retpath[0][make_path_find_last_slash(retpath[0])] = '\0';
		else
			retpath[0][make_path_find_last_slash(retpath[0]) + 1] = '\0';
	//	printf("|%c|\n", retpath[0][make_path_find_last_slash(retpath[0])]);
	//	ft_printf("retpath after |%s|\n", retpath[0]);
	}
}

void	make_path_concat(char **retpath, char **dir)
{
	char *tmp;

	if (retpath[0][ft_strlen(retpath[0]) - 1] != '/')
		make_path_manage_last_slash(retpath, PATH_ADD_SLASH);
	if (dir[0][0] == '/')
		make_path_manage_last_slash(dir, PATH_REM_SLASH);
	tmp = retpath[0];
	retpath[0] = ft_strjoin(retpath[0], dir[0]);
	free(tmp);
}

char	*make_path(char *path, char *dir)
{
	char **spliteddir;
	char *retpath;
	int i;

	i = 0;
	if (dir == NULL || ft_strlen(dir) == 0)
		return (path);
	if (!ft_strcmp(dir, "/"))
		return (retpath = ft_strdup("/"));
	if (!ft_strncmp(dir, "/", 1))
		retpath = ft_strdup("/");
	else
		retpath = ft_strdup(path);
	make_path_manage_last_slash(&retpath, PATH_REM_SLASH);
	spliteddir = ft_strsplit(dir, '/');
	while (spliteddir[i])
	{
		if (!ft_strcmp(spliteddir[i], "."))
			NULL ;
		else if (!ft_strcmp(spliteddir[i], ".."))
			make_path_dotdot(&retpath);
		else
			make_path_concat(&retpath, &spliteddir[i]);
		i++;
	}
	utils_free_2darray((void **)spliteddir);
	return (retpath);	
}

/*int	main(int argc, char **argv)
{
	char *ret;
	char *buf2;
	char **test;
	char *input;

	printf("test main for make_path()\n");
	printf("dir & subdir organisation :\n");
	printf("$> printdir()\n");
	printf("/\n");
	printf("/dir1\n");
	printf("/dir1/dir1-2\n");
	printf("/dir2\n");
	printf("/dir2/dir2-2\n");
	printf("/dir3\n");
	printf("/dir3/file1\n\n");
	
	buf2 = ft_strdup("/");
	printf("input = |dir1|\n");
	ret = make_path(buf2, "dir1");
	printf("wdir = |%s|\n", buf2); 
	printf("ret = |%s| attendu : |/dir1|\n\n", ret);
	
	buf2 = ft_strdup("/");
	printf("input = |dir1/dir1-2|\n");
	ret = make_path(buf2, "dir1/dir1-2");
	printf("wdir = |%s|\n", buf2); 
	printf("ret = |%s| attendu : |/dir1/dir1-2|\n\n", ret);

	buf2 = ft_strdup("/dir1");
	printf("input = |../dir2|\n");
	ret = make_path(buf2, "../dir2");
	printf("wdir = |%s|\n", buf2); 
	printf("ret = |%s| attendu : |/dir2|\n\n", ret);
	
	buf2 = ft_strdup("/dir1");
	printf("input = |../dir1/dir1-2/../../dir2|\n");
	ret = make_path(buf2, "../dir1/dir1-2/../../dir2");
	printf("wdir = |%s|\n", buf2); 
	printf("ret = |%s| attendu : |/dir2|\n\n", ret);
	
	buf2 = ft_strdup("/dir1/");
	printf("input = |../dir1/dir1-2/../../dir2|\n");
	ret = make_path(buf2, "../dir1/dir1-2/../../dir2");
	printf("wdir = |%s|\n", buf2); 
	printf("ret = |%s| attendu : |/dir2|\n\n", ret);
	
	buf2 = ft_strdup("/dir1/");
	printf("input = |../|\n");
	ret = make_path(buf2, "../");
	printf("wdir = |%s|\n", buf2); 
	printf("ret = |%s| attendu : |/|\n\n", ret);
	
	buf2 = ft_strdup("/dir2/");
	printf("input = |./dir2-2|\n");
	ret = make_path(buf2, "./dir2-2");
	printf("wdir = |%s|\n", buf2); 
	printf("ret = |%s| attendu : |/dir2/dir2-2|\n\n", ret);
	
	buf2 = ft_strdup("/dir2");
	printf("input = |/./dir1|\n");
	ret = make_path(buf2, "/./dir1");
	printf("wdir = |%s|\n", buf2); 
	printf("ret = |%s| attendu : |/dir1|\n\n", ret);
	
	buf2 = ft_strdup("/Users/tmaraval/work/21sh/test_scripts");
	printf("input = |/./Users|\n");
	ret = make_path(buf2, "/./Users");
	printf("wdir = |%s|\n", buf2); 
	printf("ret = |%s| attendu : |/Users|\n\n", ret);
	
	buf2 = ft_strdup("/Users/tmaraval/work/21sh/test_scripts");
	printf("input = |../../../../../|\n");
	ret = make_path(buf2, "../../../../../");
	printf("wdir = |%s|\n", buf2); 
	printf("ret = |%s| attendu : |/|\n\n", ret);
	
	buf2 = ft_strdup("/Users/tmaraval/work/21sh/test_scripts");
	printf("input = |/|\n");
	ret = make_path(buf2, "/");
	printf("wdir = |%s|\n", buf2); 
	printf("ret = |%s| attendu : |/|\n\n", ret);
}*/
