/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_arrow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 15:57:53 by tmaraval          #+#    #+#             */
/*   Updated: 2018/03/29 16:32:11 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	input_arrow_left(t_buffer *tbuffer, char *read_buf)
{
	ft_putstr(read_buf + 1);
	if (memcmp(read_buf, FT_KEY_LEFT, ft_strlen(FT_KEY_LEFT)) == 0)
	{
		ft_putstr("left arrow\n");
	}
}

void	input_arrow_right(t_buffer *tbuffer, char *read_buf)
{
	if (memcmp(read_buf, FT_KEY_RIGHT, ft_strlen(FT_KEY_RIGHT)) == 0)
	{
		ft_putstr("right arrow\n");
	}
}
