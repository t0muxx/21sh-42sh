/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 13:26:53 by tmaraval          #+#    #+#             */
/*   Updated: 2018/09/08 11:50:59 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "completion.h"
#include "utils.h"

void	completion_search_in_path(t_buffer *tbuffer, char *userinput, char **env)
{
	char *path;
	char **patharray;
	t_list *filelist;
	t_list *corresponding_filelist;

	if (userinput)
		;
	path = env_get_var("PATH", env);
	patharray = ft_strsplit(path, ':');
	free(path);
	filelist = completion_read(patharray);
	path = extract_current_word(tbuffer->buffer, tbuffer->cnt - 1);
	corresponding_filelist = completion_cmp_userinput_filelist(path, filelist);
	free(path);
	completion_print(tbuffer, corresponding_filelist);
}

void	completion_search_in_dir(t_buffer *tbuffer, char *userinput)
{
	char *searchdir[2];
	char *tocomplete;
	t_list *filelist;
	t_list *corresponding_filelist;

	searchdir[0] = completion_trim_get_searchdir(userinput);
	searchdir[1] = 0;
	tocomplete = completion_trim_get_str_to_complete(userinput);
	filelist = completion_read(searchdir);
	if (ft_strlen(tocomplete) == 0)
		corresponding_filelist = filelist;
	else
		corresponding_filelist = completion_cmp_userinput_filelist(tocomplete, filelist);
	completion_trim_append_slash(corresponding_filelist, searchdir[0]);
	completion_print(tbuffer, corresponding_filelist);
}
