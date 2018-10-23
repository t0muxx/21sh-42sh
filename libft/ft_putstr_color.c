/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 10:46:02 by tmaraval          #+#    #+#             */
/*   Updated: 2018/02/13 20:04:28 by tomlulu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_color(char *str, char *color)
{
	color = !ft_strcmp("RED", color) ? ANSI_COLOR_RED : color;
	color = !ft_strcmp("GREEN", color) ? ANSI_COLOR_GREEN : color;
	color = !ft_strcmp("YELLOW", color) ? ANSI_COLOR_YELLOW : color;
	color = !ft_strcmp("BLUE", color) ? ANSI_COLOR_BLUE : color;
	color = !ft_strcmp("MAGENTA", color) ? ANSI_COLOR_MAGENTA : color;
	color = !ft_strcmp("PURPLE", color) ? ANSI_COLOR_PURPLE : color;
	color = !ft_strcmp("CYAN", color) ? ANSI_COLOR_CYAN : color;
	ft_putstr(color);
	ft_putstr(str);
	ft_putstr(ANSI_COLOR_RESET);
}
