/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_num_flag.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 07:52:49 by tmaraval          #+#    #+#             */
/*   Updated: 2018/01/23 10:54:18 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_num_sharp_dohexa(t_parsed_opt *opt)
{
	char *temp;

	temp = opt->str_arg;
	ft_printf_precision(opt);
	if (ft_printf_flag_strarg_isnega(opt) != 0
	|| opt->ch_convert == 'p')
	{
		temp = opt->str_arg;
		opt->str_arg = ft_strjoin("0x", opt->str_arg);
		free(temp);
	}
}

void	ft_printf_num_sharp(t_parsed_opt *opt)
{
	char *temp;

	if (opt->bin_flag & FLG_SHARP || opt->ch_convert == 'p')
	{
		if (opt->ch_convert == 'o' || opt->ch_convert == 'O')
		{
			temp = opt->str_arg;
			if (ft_printf_flag_strarg_isnega(opt) != 0)
			{
				temp = opt->str_arg;
				opt->str_arg = ft_strjoin("0", opt->str_arg);
				free(temp);
			}
			ft_printf_precision(opt);
		}
		if (opt->ch_convert == 'x' || opt->ch_convert == 'X'
		|| opt->ch_convert == 'p')
			ft_printf_num_sharp_dohexa(opt);
	}
}

void	ft_printf_num_manage_flag(t_parsed_opt *opt)
{
	char *temp;

	ft_printf_num_sharp(opt);
	if (opt->bin_flag & FLG_SP && ft_strchr("di", opt->ch_convert))
	{
		if (opt->str_arg[0] != '-')
		{
			ft_printf_precision(opt);
			temp = opt->str_arg;
			opt->str_arg = ft_strjoin(" ", opt->str_arg);
			free(temp);
		}
	}
	if (opt->bin_flag & FLG_PLUS && ft_strchr("di", opt->ch_convert))
	{
		if (opt->str_arg[0] != '-')
		{
			ft_printf_precision(opt);
			temp = opt->str_arg;
			opt->str_arg = ft_strjoin("+", opt->str_arg);
			free(temp);
		}
	}
}
