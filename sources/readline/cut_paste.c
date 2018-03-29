/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_paste.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 08:58:01 by tmaraval          #+#    #+#             */
/*   Updated: 2018/03/29 11:51:39 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "cursor.h"

void	cut_paste_do_cut(t_buffer *tbuffer)
{
	int i;

	i = 0;
	ft_memcpy(tbuffer->cutbuffer, tbuffer->buffer + tbuffer->cutstart, tbuffer->cutend - tbuffer->cutstart); 
	while (i++ < (tbuffer->cutend - tbuffer->cutstart))
		string_delete_char(&tbuffer->buffer, tbuffer->cutstart);
	cursor_reset_line(tbuffer);
}

void	cut_paste_do_paste(t_buffer *tbuffer)
{
	ft_memcpy(tbuffer->cutbuffer, tbuffer->buffer + tbuffer->cutstart, tbuffer->cutend - tbuffer->cutstart); 
	cursor_reset_line(tbuffer);
}
