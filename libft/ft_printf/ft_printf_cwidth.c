/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_cwidth.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 15:11:26 by tmaraval          #+#    #+#             */
/*   Updated: 2018/01/23 10:46:05 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_wcstr_width(t_parsed_opt *opt)
{
	wchar_t *temp;

	while (ft_wcstrlen(opt->wstr_arg) < (size_t)opt->in_width)
	{
		temp = opt->wstr_arg;
		if (opt->bin_flag & FLG_ZERO && (opt->bin_flag & FLG_MINUS) == 0)
			opt->wstr_arg = ft_wcstrjoin(L"0", opt->wstr_arg);
		else if (opt->bin_flag & FLG_MINUS)
			opt->wstr_arg = ft_wcstrjoin(opt->wstr_arg, L" ");
		else
			opt->wstr_arg = ft_wcstrjoin(L" ", opt->wstr_arg);
		free(temp);
	}
}

void	ft_printf_width_dowidth(t_parsed_opt *opt)
{
	char *temp;

	temp = opt->str_arg;
	if (opt->bin_flag & FLG_ZERO && (opt->bin_flag & FLG_MINUS) == 0)
		opt->str_arg = ft_strjoin("0", opt->str_arg);
	else if (opt->bin_flag & FLG_MINUS)
		opt->str_arg = ft_strjoin(opt->str_arg, " ");
	else
		opt->str_arg = ft_strjoin(" ", opt->str_arg);
	free(temp);
}

void	ft_printf_cwidth(t_parsed_opt *opt)
{
	if (opt->ch_convert == -1)
	{
		while ((int)ft_strlen(opt->str_arg) < opt->in_width)
			ft_printf_width_dowidth(opt);
	}
	else
	{
		if (opt->ch_convert == 'c' && opt->str_arg[0] == '\0')
			opt->in_width -= 1;
		while ((int)ft_strlen(opt->str_arg) < opt->in_width)
			ft_printf_width_dowidth(opt);
	}
}
