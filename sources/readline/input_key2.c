/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_key2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 13:28:15 by tmaraval          #+#    #+#             */
/*   Updated: 2018/09/07 11:01:03 by tmaraval         ###   ########.fr       */
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

//	ft_printf("userinput |%s|\n", userinput);
	searchdir[0] = completion_trim_get_searchdir(userinput);
//	ft_printf("searchdir |%s|\n", searchdir[0]);
	searchdir[1] = 0;
	tocomplete = completion_trim_get_str_to_complete(userinput);
//	ft_printf("tocomplete |%s|\n", tocomplete);
	filelist = completion_read(searchdir);
	corresponding_filelist = completion_cmp_userinput_filelist(tocomplete, filelist);
	completion_trim_append_slash(corresponding_filelist, searchdir[0]);
	completion_print(tbuffer, corresponding_filelist);
}

void	input_tab(t_buffer *tbuffer, char *read_buf)
{
	int		first_word;
	char	*tocomplete;

	first_word = 0;
	if (ft_strlen(read_buf) == 1 && read_buf[0] == 9)
	{
		tocomplete = extract_current_word(tbuffer->buffer, tbuffer->cnt - 1);
		if ((first_word = completion_in_first_word(tbuffer->buffer, tbuffer->cnt)) == 1)
		{
			completion_search_in_path(tbuffer, tocomplete, tbuffer->env);
		}
		else
			completion_search_in_dir(tbuffer, tocomplete);
	}
}
