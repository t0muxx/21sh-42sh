/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 13:58:48 by tmaraval          #+#    #+#             */
/*   Updated: 2018/10/11 11:44:36 by tmaraval         ###   ########.fr       */
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

int		completion_find_lastcmd(char *userinput, int pos)
{
	int i;

	i = pos;
	if (ft_strlen(userinput) == 0)
		return (0);
	while (i > 0 &&
	(userinput[i] != '|' && userinput[i] != ';' && userinput[i] != '&'))
		i--;
	if (userinput[i] == '|' || userinput[i] == ';' || userinput[i] == '&')
		i++;
	while (userinput[i] == ' ')
		i++;
	return (i);
}

void	completion_read_from_dirs(char **dirs, t_list **filelist)
{
	int				i;
	DIR				*pdir;
	struct dirent	*dir;
	t_list			*new;

	i = 0;
	while (dirs[i])
	{
		if ((pdir = opendir(dirs[i])) != NULL)
		{
			while ((dir = readdir(pdir)) != NULL)
			{
				if (ft_strcmp(dir->d_name, ".") && ft_strcmp(dir->d_name, ".."))
				{
					new = ft_lstnew(dir->d_name, ft_strlen(dir->d_name) + 1);
					ft_lst_sortedinsert(filelist, new);
				}
			}
			closedir(pdir);
		}
		i++;
	}
}

t_list	*completion_read(char **dirs)
{
	t_list *filelist;

	filelist = NULL;
	completion_read_from_dirs(dirs, &filelist);
	return (filelist);
}
