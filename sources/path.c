/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 11:13:48 by tmaraval          #+#    #+#             */
/*   Updated: 2018/09/04 09:39:55 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "readline.h"
#include "utils.h"

char	*path_find_in_path(char *name, char **env)
{
	char 	**patharray;
	char 	*path;
	int 	i;

	i = 0;
	if (!(path = env_get_var("PATH", env)))
		return (NULL);
	patharray = ft_strsplit(path, ':');
	free(path);
	if (name[0] == '/' || (!ft_strncmp(name, "./", 2))
	|| (!ft_strncmp(name, "../", 3)))
	{
		if (access(name, F_OK) == 0 && access(name, X_OK) == 0)
			return (name);
		else if (access(name, F_OK) == 0 && access(name, X_OK) == -1)
			error_print(2, name, "");
		else if (access(name, F_OK) == -1)
			error_print(3, name, "");
		exit(EXIT_FAILURE);
	}
	while (patharray[i])
	{
		path = make_path(patharray[i], name);
		if (access(path, F_OK) == -1)
			ft_strdel(&path);
		else
			break ;
		i++;
	}
	utils_free_2darray((void **)patharray);
	return (path);
}
