/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   makepath_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 11:44:12 by tmaraval          #+#    #+#             */
/*   Updated: 2018/09/14 11:42:07 by tmaraval         ###   ########.fr       */
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
