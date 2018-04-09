/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 17:55:46 by tmaraval          #+#    #+#             */
/*   Updated: 2018/03/30 09:12:03 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	prompt_print(t_buffer *tbuffer)
{
	if (tbuffer->state == READ_NORMAL && tbuffer->line == 1)
	{
		write(1, "$> ", 3);
		tbuffer->prompt_len = 3;
	}
	if (tbuffer->state == READ_IN_QUOTE)
	{
		write(1, "> ", 2);
		tbuffer->prompt_len = 2;
	}
}
