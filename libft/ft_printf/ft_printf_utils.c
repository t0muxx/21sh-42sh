/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlulu <tomlulu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 14:31:40 by tomlulu           #+#    #+#             */
/*   Updated: 2018/01/23 11:41:10 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_parser_read_int_upd_str_loop(char **format, int *ret)
{
	while (ft_isdigit(**format))
	{
		if (*ret > INT_MAX)
			*ret = -1;
		else
		{
			*ret *= 10;
			*ret += **format - '0';
		}
		(*format)++;
	}
}

int		ft_parser_read_int_upd_str(char **format)
{
	int ret;
	int isnega;

	ret = 0;
	isnega = FALSE;
	if (**format == '-')
	{
		(*format)++;
		ret = **format - '0';
		isnega = TRUE;
	}
	else if (ft_isdigit(**format))
		ret = **format - '0';
	else
		return (0);
	(*format)++;
	ft_parser_read_int_upd_str_loop(format, &ret);
	if (isnega == TRUE)
		ret *= -1;
	return (ret);
}
