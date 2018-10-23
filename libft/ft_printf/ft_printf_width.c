/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_width.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlulu <tomlulu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/14 14:39:10 by tomlulu           #+#    #+#             */
/*   Updated: 2018/01/31 08:09:22 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_width_dosharp_zero(t_parsed_opt *opt)
{
	char *temp;

	if (opt->bin_flag & FLG_SHARP && (opt->ch_convert == 'x'
	|| opt->ch_convert == 'X'))
	{
		opt->in_width -= 2;
		temp = opt->str_arg;
		opt->str_arg = ft_strsub(opt->str_arg, 2, ft_strlen(opt->str_arg));
		free(temp);
		while ((int)ft_strlen(opt->str_arg) < opt->in_width)
		{
			temp = opt->str_arg;
			opt->str_arg = ft_strjoin("0", opt->str_arg);
			free(temp);
		}
		temp = opt->str_arg;
		opt->str_arg = ft_strjoin("0x", opt->str_arg);
		free(temp);
	}
}

void	ft_printf_width_sign(t_parsed_opt *opt)
{
	char sign[2];
	char *temp;

	sign[0] = opt->str_arg[0];
	temp = opt->str_arg;
	opt->str_arg = ft_strsub(opt->str_arg, 1, ft_strlen(opt->str_arg));
	free(temp);
	while ((int)ft_strlen(opt->str_arg) + 1 < opt->in_width)
	{
		temp = opt->str_arg;
		opt->str_arg = ft_strjoin("0", opt->str_arg);
		free(temp);
	}
	temp = opt->str_arg;
	sign[1] = '\0';
	opt->str_arg = ft_strjoin(sign, opt->str_arg);
	free(temp);
}

void	ft_printf_width_doit(t_parsed_opt *opt)
{
	char *temp;

	if (opt->str_arg[0] == '+' || opt->str_arg[0] == '-'
	|| opt->str_arg[0] == ' ')
		ft_printf_width_sign(opt);
	else
	{
		while ((int)ft_strlen(opt->str_arg) < opt->in_width)
		{
			temp = opt->str_arg;
			opt->str_arg = ft_strjoin("0", opt->str_arg);
			free(temp);
		}
	}
}

void	ft_printf_width_dolen0(t_parsed_opt *opt)
{
	char *temp;

	if (opt->str_arg[0] == '\0' || ft_strlen(opt->str_arg) == 0)
	{
		free(opt->str_arg);
		opt->str_arg = ft_strdup(" ");
		while ((int)ft_strlen(opt->str_arg) < opt->in_width)
		{
			temp = opt->str_arg;
			opt->str_arg = ft_strjoin(" ", opt->str_arg);
			free(temp);
		}
	}
	else
		ft_printf_width_do(opt);
}

void	ft_printf_width(t_parsed_opt *opt)
{
	if (opt->bin_flag & FLG_ZERO && opt->in_precision == -1)
	{
		ft_printf_width_dosharp_zero(opt);
		ft_printf_width_doit(opt);
	}
	if (opt->in_width > 0)
		ft_printf_width_dolen0(opt);
}
