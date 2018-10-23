/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_width_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 08:12:51 by tmaraval          #+#    #+#             */
/*   Updated: 2018/01/24 08:15:06 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_width_do(t_parsed_opt *opt)
{
	char *temp;

	while ((int)ft_strlen(opt->str_arg) < opt->in_width)
	{
		temp = opt->str_arg;
		if (opt->bin_flag & FLG_MINUS)
		{
			opt->str_arg = ft_strjoin(opt->str_arg, " ");
			free(temp);
		}
		else
		{
			opt->str_arg = ft_strjoin(" ", opt->str_arg);
			free(temp);
		}
	}
}
