/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 14:11:08 by tmaraval          #+#    #+#             */
/*   Updated: 2018/08/21 16:00:21 by tomux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_do_wchar(t_parsed_opt *opt, va_list curr_arg)
{
	wchar_t ch;

	ch = va_arg(curr_arg, wchar_t);
	if (ch <= 0x7f)
		opt->str_arg[0] = ch;
	else if (ch <= 0x7FF)
	{
		opt->str_arg[0] = 0xC0 | ((ch >> 6) & 0x1F);
		opt->str_arg[1] = 0x80 | (ch & 0x3F);
	}
	else if (ch <= 0xFFFF)
	{
		opt->str_arg[0] = 0xE0 | ((ch >> 12) & 0x0F);
		opt->str_arg[1] = 0x80 | ((ch >> 6) & 0x3F);
		opt->str_arg[2] = 0x80 | (ch & 0x3F);
	}
	else if (ch <= 0x10FFFF)
	{
		opt->str_arg[0] = 0xF0 | ((ch >> 18) & 0x07);
		opt->str_arg[1] = 0x80 | ((ch >> 12) & 0x3F);
		opt->str_arg[2] = 0x80 | ((ch >> 6) & 0x3F);
		opt->str_arg[3] = 0x80 | (ch & 0x3F);
	}
	else
		NULL;
}

void	ft_conv_char(t_parsed_opt *opt, va_list curr_arg)
{
	opt->str_arg = ft_memalloc(5);
	ft_bzero(opt->str_arg, 5);
	if (opt->bin_lenmod & LENMOD_L || opt->ch_convert == 'C')
	{
		ft_do_wchar(opt, curr_arg);
	}
	else if (opt->ch_convert == '%')
		opt->str_arg[0] = '%';
	else
		opt->str_arg[0] = (char)va_arg(curr_arg, int);
	if (opt->str_arg[0] == '\0')
		opt->ch_ch = opt->str_arg[0];
}
