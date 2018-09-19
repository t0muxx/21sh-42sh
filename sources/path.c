/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 11:13:48 by tmaraval          #+#    #+#             */
/*   Updated: 2018/09/19 12:10:46 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "readline.h"
#include "utils.h"

int		path_find_in_path_nocat(char *name)
{
	if (access(name, F_OK) == 0 && access(name, X_OK) == 0)
		return (0);
	else if (access(name, F_OK) == 0 && access(name, X_OK) == -1)
		error_print(2, name, "");
	else if (access(name, F_OK) == -1)
		error_print(3, name, "");
	return (-1);
}

void	path_find_in_path_loop(char **patharray, char *name, char **path)
{
	int i;

	i = 0;
	while (patharray[i])
	{
		path[0] = make_path(patharray[i], name);
		if (access(path[0], F_OK) == -1)
			ft_strdel(&path[0]);
		else
			break ;
		i++;
	}
}

char	*path_find_in_path(char *name, char **env)
{
	char 	**patharray;
	char 	*path;

	if (name[0] == '/' || (!ft_strncmp(name, "./", 2))
	|| (!ft_strncmp(name, "../", 3)))
	{
		if (path_find_in_path_nocat(name) == 0)
			return (name);
		exit(EXIT_FAILURE);
	}
	if (!(path = env_get_var("PATH", env)))
		return (NULL);
	patharray = ft_strsplit(path, ':');
	free(path);
	path_find_in_path_loop(patharray, name, &path);
	utils_free_2darray((void **)patharray);
	return (path);
}
