/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_key2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 13:28:15 by tmaraval          #+#    #+#             */
/*   Updated: 2018/09/08 11:48:16 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "completion.h"
#include "utils.h"

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
