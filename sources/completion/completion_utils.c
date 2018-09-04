/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 13:58:48 by tmaraval          #+#    #+#             */
/*   Updated: 2018/09/04 15:35:05 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include "../../includes/libft.h"

void	completion_add_file(struct dirent *dir, char **filelist)
{
	char *tmp;

	if (*filelist == NULL)
		*filelist = ft_strdup(dir->d_name);
	else
	{
		tmp = *filelist;
		*filelist = ft_strjoin(*filelist, dir->d_name);
		free(tmp);
	}
	tmp = *filelist;
	*filelist = ft_strjoin(*filelist, ";");
	free(tmp);
}

char 	*completion_read_from_dirs(char **dirs)
{
	int		i;
	DIR		*pdir;
	struct 	dirent *dir;
	char	*filelist;

	filelist = NULL;
	i = 0;
	while (dirs[i])
	{
		if ((pdir = opendir(dirs[i])) != NULL)
		{
			while ((dir = readdir(pdir)) != NULL)
				completion_add_file(dir, &filelist);
		}
		closedir(pdir);
		i++;
	}
	return (filelist);
}

char **completion_read(char **dirs)
{
	char *filelist;
	char **ret;

	filelist = completion_read_from_dirs(dirs);
	free(filelist);
	ret = ft_strsplit(filelist, ';');
	return (ret);
}

/*int		main(int argc, char **argv)
{
	int		i;
	char	*dirs[2];
	char	**ret;

	i = 0;
	dirs[0] = argv[1];
	dirs[1] = 0;
	ft_putendl(dirs[0]);
	ret = completion_read(dirs);
	while (ret[i])
	{
		ft_putendl(ret[i]);
		i++;
	}
	i = 0;
	while (ret[i])
	{
		free(ret[i]);
		i++;
	}
	free(ret);
	return (0);
}*/
