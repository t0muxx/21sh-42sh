/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 08:17:44 by tmaraval          #+#    #+#             */
/*   Updated: 2018/02/22 08:20:30 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 ** cursor_move_left move the cursor from count line to the left
 ** using the ansi escape code
*/

void	cursor_move_left(int count)
{
	char *temp;

	ft_putstr("\033[");
	temp = ft_itoa(count);
	ft_putstr(temp);
	ft_putstr("D");
	free(temp);
}

/*
 ** cursor_move_right move the cursor from count line to the right
 ** using the ansi escape code
*/

void	cursor_move_right(int count)
{
	char *temp;

	ft_putstr("\033[");
	temp = ft_itoa(count);
	ft_putstr(temp);
	ft_putstr("C");
	free(temp);
}
