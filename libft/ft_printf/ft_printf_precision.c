/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_precision.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlulu <tomlulu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/14 10:08:03 by tomlulu           #+#    #+#             */
/*   Updated: 2018/01/23 11:40:42 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_precision_printzero(t_parsed_opt *opt)
{
	if (opt->in_precision == 0 && !(opt->bin_flag & FLG_SHARP)
	&& ft_strcmp("0", opt->str_arg) == 0)
		opt->str_arg[0] = '\0';
	else if ((opt->bin_flag & FLG_SHARP) && !(ft_strchr("oO", opt->ch_convert))
	&& opt->in_precision == 0 && ft_strcmp("0", opt->str_arg) == 0)
		opt->str_arg[0] = '\0';
}

void	ft_printf_precision_sign(t_parsed_opt *opt)
{
	char sign[2];
	char *temp;

	sign[0] = opt->str_arg[0];
	temp = opt->str_arg;
	opt->str_arg = ft_strsub(opt->str_arg, 1, ft_strlen(opt->str_arg));
	free(temp);
	while (ft_strlen(opt->str_arg) < (size_t)opt->in_precision)
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

void	ft_printf_precision(t_parsed_opt *opt)
{
	char	*temp;

	if (ft_strchr("oOxXdupiDU", opt->ch_convert) && opt->in_precision > 0)
	{
		if (opt->str_arg[0] == '-' || opt->str_arg[0] == '+')
			ft_printf_precision_sign(opt);
		else
		{
			while ((int)ft_strlen(opt->str_arg) < opt->in_precision)
			{
				temp = opt->str_arg;
				opt->str_arg = ft_strjoin("0", opt->str_arg);
				free(temp);
			}
		}
	}
	ft_printf_precision_printzero(opt);
}
