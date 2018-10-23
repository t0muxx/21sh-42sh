/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str_precision.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 16:26:55 by tmaraval          #+#    #+#             */
/*   Updated: 2018/01/23 09:30:38 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_wcstr_precision(t_parsed_opt *opt)
{
	wchar_t *temp;

	if (opt->in_precision != -1)
	{
		temp = opt->wstr_arg;
		opt->wstr_arg = ft_wcstrsub(opt->wstr_arg, 0, opt->in_precision);
		free(temp);
	}
}

void	ft_printf_str_precision(t_parsed_opt *opt)
{
	char *temp;

	if (opt->in_precision != -1)
	{
		temp = opt->str_arg;
		opt->str_arg = ft_strsub(opt->str_arg, 0, opt->in_precision);
		free(temp);
	}
}
