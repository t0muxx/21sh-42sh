/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 13:58:48 by tmaraval          #+#    #+#             */
/*   Updated: 2018/09/07 09:08:18 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include "../../includes/libft.h"
#include <unistd.h>

int		completion_in_first_word(char *userinput, int pos)
{
	int i;

	i = 0;
	while (userinput[i])
	{
		if (userinput[i] == ' ')
			break ;
		i++;
	}
	if (i > pos - 1 || i == (int)ft_strlen(userinput))
		return (1);
	return (0);
}

void	completion_read_from_dirs(char **dirs, t_list **filelist)
{
	int		i;
	DIR		*pdir;
	struct 	dirent	*dir;
	t_list		*new;

	i = 0;
	while (dirs[i])
	{
		if ((pdir = opendir(dirs[i])) != NULL)
		{
			while ((dir = readdir(pdir)) != NULL)
			{
				new = ft_lstnew(dir->d_name, ft_strlen(dir->d_name) + 1);
				ft_lstadd(filelist, new);
			}
		}
		closedir(pdir);
		i++;
		}
}

t_list *completion_read(char **dirs)
{
	t_list *filelist;
			
	filelist = NULL;
	completion_read_from_dirs(dirs, &filelist);
	return (filelist);
}

/*int		main(int argc, char **argv)
{
	char	*dirs[2];
	char	**ret;
	t_list  *list;

	dirs[0] = argv[1];
	dirs[1] = 0;
	ft_putendl(dirs[0]);
	list = completion_read(dirs);
	while (list)
	{
		ft_putendl(list->content);
		list = list->next;
	}
	return (0);
}*/
