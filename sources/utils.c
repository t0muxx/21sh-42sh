/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlulu <tomlulu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 18:02:52 by tomlulu           #+#    #+#             */
/*   Updated: 2018/02/15 16:29:50 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	utils_makepath_manage_ddot(char **pwd, char **directory, char *abspath)
{
	int		i;
	int		lenpwd;
	char	*newpath;

	lenpwd = 0;
	i = 0;
	if (directory[0][0] == '.' && directory[0][1] == '.')
	{
		lenpwd = ft_strlen(pwd[0]);
		if (pwd[0][lenpwd] == '/')
		{
			lenpwd--;
			i++;
		}
		while (pwd[0][lenpwd] != '/')
		{
			lenpwd--;
			i++;
		}
		newpath = ft_strsub(pwd[0], 0, ft_strlen(pwd[0]) - i);
		directory[0] = directory[0] + 3;
		utils_makepath_cpy(newpath, directory[0], abspath);
		free(newpath);
	}
}

void	utils_makepath_cpy(char *pwd, char *directory, char *abspath)
{
	if (pwd[ft_strlen(pwd) - 1] == '/')
	{
		ft_strcpy(abspath, pwd);
		if (directory[ft_strlen(directory) - 1] == '/')
			ft_strncat(abspath, directory, ft_strlen(directory) - 1);
		else
			ft_strncat(abspath, directory, ft_strlen(directory));
	}
	else
	{
		ft_strcpy(abspath, pwd);
		ft_strcat(abspath, "/");
		if (directory[ft_strlen(directory) - 1] == '/')
			ft_strncat(abspath, directory, ft_strlen(directory) - 1);
		else
			ft_strncat(abspath, directory, ft_strlen(directory));
	}
}

char	*utils_makepath(char *pwd, char *directory)
{
	char *abspath;

	if (!((abspath = (char *)malloc(sizeof(char) * PATH_MAX))))
		error_malloc_err();
	if (*directory == '/' || !directory || !pwd)
	{
		free(abspath);
		return (NULL);
	}
	if (directory[0] == '.' && directory[1] == '/')
		utils_makepath_cpy(pwd, directory + 2, abspath);
	else if (directory[0] == '.' && directory[1] == '.')
		utils_makepath_manage_ddot(&pwd, &directory, abspath);
	else
		utils_makepath_cpy(pwd, directory, abspath);
	return (abspath);
}
