/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 10:29:20 by tmaraval          #+#    #+#             */
/*   Updated: 2018/02/22 18:59:17 by tomlulu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int		ft_conv_do_print(t_parsed_opt *opt)
{
	int ret;

	ret = 0;
	if (opt->str_arg != NULL)
	{
		if ((opt->ch_convert == 'c' || opt->ch_convert == 'C'))
		{
			if (opt->ch_ch == 0)
			{
				write(1, opt->str_arg, ft_strlen(opt->str_arg) + 1);
				free(opt->str_arg);
				return (ft_strlen(opt->str_arg) + 1);
			}
			else
			{
				write(1, opt->str_arg, ft_strlen(opt->str_arg));
				free(opt->str_arg);
				return (ft_strlen(opt->str_arg));
			}
		}
		ret = (int)ft_strlen(opt->str_arg);
		write(1, opt->str_arg, ft_strlen(opt->str_arg));
		free(opt->str_arg);
	}
	return (ret);
}

void	ft_conv_do_conv(t_parsed_opt *opt, va_list curr_arg)
{
	if (ft_strchr("oOxXdDuUpi", opt->ch_convert))
	{
		ft_conv_integer(opt, curr_arg);
		ft_printf_num_manage_flag(opt);
		ft_printf_precision(opt);
		ft_printf_width(opt);
		if (opt->ch_convert == 'X')
			ft_strupcase(opt->str_arg);
	}
	if (ft_strchr("cC%", opt->ch_convert))
	{
		ft_conv_char(opt, curr_arg);
		ft_printf_cwidth(opt);
	}
	if (ft_strchr("sS", opt->ch_convert))
	{
		ft_conv_str(opt, curr_arg);
		ft_printf_str_precision(opt);
		ft_printf_cwidth(opt);
	}
}

int		ft_conv_do_noconvert(t_parsed_opt *opt, char **format)
{
	int ret;

	opt->str_arg = ft_strsub(*format, 0, 1);
	(*format)++;
	ft_printf_cwidth(opt);
	ret = (int)ft_strlen(opt->str_arg);
	write(1, opt->str_arg, ft_strlen(opt->str_arg));
	free(opt->str_arg);
	return (ret);
}

int		ft_conv(t_parsed_opt *opt, va_list curr_arg, char **format)
{
	int ret;

	ret = 0;
	if (opt->ch_convert == -1)
		ret = ft_conv_do_noconvert(opt, format);
	else
	{
		ft_conv_do_conv(opt, curr_arg);
		ret = ft_conv_do_print(opt);
	}
	return (ret);
}
