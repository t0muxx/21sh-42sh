/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 13:26:53 by tmaraval          #+#    #+#             */
/*   Updated: 2018/11/21 09:10:01 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "completion.h"
#include "utils.h"

void	completion_trim_tild(char **searchdir, char ***env)
{
	char *path;
	char *path2;

	path = NULL;
	path2 = NULL;
	if (!ft_strncmp(searchdir[0], "~/", 2))
	{
		if ((path = env_get_var("HOME", *env)) == NULL)
		{
			ft_putendl_fd("\nHome is not defined, can't expand", 2);
			return ;
		}
		path2 = ft_strdup(searchdir[0]);
		free(searchdir[0]);
		searchdir[0] = ft_strjoin(path, path2 + 1);
		free(path);
		free(path2);
	}
}

void	completion_search_in_path(t_buffer *tbuffer, char **env)
{
	char	*path;
	char	**patharray;
	t_list	*filelist;
	t_list	*corresponding_filelist;

	if ((path = env_get_var("PATH", env)) == NULL)
		return ;
	patharray = ft_strsplit(path, ':');
	free(path);
	filelist = completion_read(patharray);
	utils_free_2darray((void **)patharray);
	path = extract_current_word(tbuffer->buffer, tbuffer->cnt - 1);
	corresponding_filelist = completion_cmp_userinput_filelist(path, filelist);
	free(path);
	completion_print(tbuffer, corresponding_filelist);
	ft_lst_free(filelist);
	ft_lst_free(corresponding_filelist);
}

void	completion_search_in_dir(t_buffer *tbuffer, char *userinput)
{
	char	*searchdir[2];
	char	*tocomplete;
	t_list	*filelist;
	t_list	*cf;

	searchdir[0] = completion_trim_get_searchdir(userinput);
	completion_trim_tild(searchdir, &tbuffer->env);
	searchdir[1] = 0;
	tocomplete = completion_trim_get_str_to_complete(userinput);
	filelist = completion_read(searchdir);
	if (ft_strlen(tocomplete) == 0)
		cf = filelist;
	else
		cf = completion_cmp_userinput_filelist(tocomplete, filelist);
	completion_trim_append_slash(cf, searchdir);
	completion_print(tbuffer, cf);
	ft_lst_free(filelist);
	if (ft_strlen(tocomplete) != 0)
		ft_lst_free(cf);
	free(tocomplete);
	free(searchdir[0]);
}
