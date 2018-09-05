/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_key2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 13:28:15 by tmaraval          #+#    #+#             */
/*   Updated: 2018/09/05 15:54:00 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "completion.h"
#include "utils.h"

void	completion_search_in_path(char *userinput, char **env)
{
	char *path;
	char **patharray;
	t_list *filelist;
	t_list *corresponding_filelist;

	path = env_get_var("PATH", env);
	patharray = ft_strsplit(path, ':');
	free(path);
	filelist = completion_read(patharray);
	corresponding_filelist = completion_cmp_userinput_filelist(userinput, filelist);
	ft_putendl("");
	while (corresponding_filelist)
	{
		ft_printf("%s\n", corresponding_filelist->content);
		corresponding_filelist = corresponding_filelist->next;
	}

}

void	input_tab(t_buffer *tbuffer, char *read_buf)
{
	int		first_word;
	char	*tocomplete;

	first_word = 0;
	if (ft_strlen(read_buf) == 1 && read_buf[0] == 9)
	{
		tocomplete = extract_current_word(tbuffer->buffer, tbuffer->cnt);
		if ((first_word = completion_in_first_word(tbuffer->buffer, tbuffer->cnt)) == 1)
		{
			completion_search_in_path(tocomplete, tbuffer->env);
		}
		else
			;	
	}
}
