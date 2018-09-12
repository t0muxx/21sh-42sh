/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_key2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 13:28:15 by tmaraval          #+#    #+#             */
/*   Updated: 2018/09/12 10:14:55 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "completion.h"
#include "utils.h"

void	input_tab(t_buffer *tbuffer, char *read_buf)
{
	int		first_word;
	char	*tocomplete;
	int		i;

	i = 0;
	first_word = 0;
	tocomplete = NULL;
	if (ft_strlen(read_buf) == 1 && read_buf[0] == 9)
	{
		tocomplete = extract_current_word(tbuffer->buffer, tbuffer->cnt - 1);
		i = completion_find_lastcmd(tbuffer->buffer, tbuffer->cnt);
		if ((first_word = completion_in_first_word(tbuffer->buffer + i, tbuffer->cnt)) == 1
		&& ft_strncmp(tocomplete, "./", 2) != 0 && ft_strncmp(tocomplete, "../", 3)
		&& tbuffer->mline != 1
		&& tocomplete[0] != '/')
			completion_search_in_path(tbuffer, tbuffer->env);
		else
			completion_search_in_dir(tbuffer, tocomplete);
		free(tocomplete);
	}
}
