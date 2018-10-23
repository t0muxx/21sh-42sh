/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flag_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 09:37:28 by tmaraval          #+#    #+#             */
/*   Updated: 2018/01/16 09:37:57 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf_flag_strarg_isnega(t_parsed_opt *opt)
{
	int i;

	i = 0;
	while (opt->str_arg[i])
	{
		if (ft_strchr("123456789abcdef", opt->str_arg[i]) != NULL)
			return (1);
		i++;
	}
	return (0);
}
