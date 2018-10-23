/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_integer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 10:22:35 by tmaraval          #+#    #+#             */
/*   Updated: 2018/01/23 10:21:27 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_conv_int_arg_hlenmod(t_parsed_opt *opt, va_list curr_arg)
{
	if (opt->bin_lenmod & LENMOD_H)
	{
		if (ft_strchr("di", opt->ch_convert))
			opt->str_arg = ft_lltoa_base((short int)va_arg(curr_arg, int),
			opt->in_base);
		else
			opt->str_arg = ft_ulltoa_base(
			(unsigned short int)va_arg(curr_arg, int), opt->in_base);
	}
	if (opt->bin_lenmod & LENMOD_HH)
	{
		if (ft_strchr("di", opt->ch_convert))
			opt->str_arg = ft_lltoa_base(
			(char)va_arg(curr_arg, int), opt->in_base);
		else
			opt->str_arg = ft_ulltoa_base(
			(unsigned char)va_arg(curr_arg, int), opt->in_base);
	}
}

void	ft_conv_int_arg_llenmod(t_parsed_opt *opt, va_list curr_arg)
{
	if (opt->bin_lenmod & LENMOD_L)
	{
		if (ft_strchr("di", opt->ch_convert))
			opt->str_arg = ft_lltoa_base(
			(long int)va_arg(curr_arg, long), opt->in_base);
		else
			opt->str_arg = ft_ulltoa_base(
			(unsigned long int)va_arg(curr_arg, long), opt->in_base);
	}
	if (opt->bin_lenmod & LENMOD_LL)
	{
		if (ft_strchr("di", opt->ch_convert))
			opt->str_arg = ft_lltoa_base(
			(long long)va_arg(curr_arg, long long), opt->in_base);
		else
			opt->str_arg = ft_ulltoa_base((unsigned long long)
			va_arg(curr_arg, unsigned long long), opt->in_base);
	}
}

int		ft_conv_int_arg_wlenmod(t_parsed_opt *opt, va_list curr_arg)
{
	ft_conv_int_arg_hlenmod(opt, curr_arg);
	ft_conv_int_arg_llenmod(opt, curr_arg);
	if (opt->bin_lenmod & LENMOD_J)
	{
		if (ft_strchr("di", opt->ch_convert))
			opt->str_arg = ft_lltoa_base(
			va_arg(curr_arg, INTMAX_T), opt->in_base);
		else
			opt->str_arg = ft_ulltoa_base(
			va_arg(curr_arg, UINTMAX_T), opt->in_base);
	}
	if (opt->bin_lenmod & LENMOD_Z)
	{
		if (ft_strchr("di", opt->ch_convert))
			opt->str_arg = ft_lltoa_base(
			(size_t)va_arg(curr_arg, size_t), opt->in_base);
		else
			opt->str_arg = ft_ulltoa_base(
			(size_t)va_arg(curr_arg, size_t), opt->in_base);
	}
	return (0);
}

void	ft_conv_int_arg(t_parsed_opt *opt, va_list curr_arg)
{
	if (opt->ch_convert == 'D')
		opt->str_arg = ft_lltoa_base(
		(long long)va_arg(curr_arg, long long), 10);
	if (opt->ch_convert == 'u')
		opt->str_arg = ft_ulltoa_base(
		(unsigned long long)va_arg(curr_arg, unsigned int), 10);
	if (opt->ch_convert == 'U')
		opt->str_arg = ft_ulltoa_base(
		(unsigned long long)va_arg(curr_arg, unsigned long), 10);
	if (opt->ch_convert == 'x')
		opt->str_arg = ft_ulltoa_base(
		(unsigned long long)va_arg(curr_arg, unsigned int), 16);
	if (opt->ch_convert == 'X')
		opt->str_arg = ft_ulltoa_base(
		(unsigned long long)va_arg(curr_arg, unsigned int), 16);
	if (opt->ch_convert == 'o')
		opt->str_arg = ft_ulltoa_base(
		(unsigned long long)va_arg(curr_arg, unsigned int), 8);
	if (opt->ch_convert == 'O')
		opt->str_arg = ft_ulltoa_base(
		(unsigned long long)va_arg(curr_arg, unsigned long), 8);
	if (opt->ch_convert == 'p')
		opt->str_arg = ft_lltoa_base(
		(long long)va_arg(curr_arg, void *), 16);
}

int		ft_conv_integer(t_parsed_opt *opt, va_list curr_arg)
{
	if (opt->bin_lenmod && !ft_strchr("DUO", opt->ch_convert))
		ft_conv_int_arg_wlenmod(opt, curr_arg);
	else
	{
		if (opt->ch_convert == 'd' || opt->ch_convert == 'i')
			opt->str_arg = ft_lltoa_base(
			(long long)va_arg(curr_arg, int), 10);
		ft_conv_int_arg(opt, curr_arg);
	}
	return (0);
}
