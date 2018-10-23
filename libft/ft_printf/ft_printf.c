/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 10:57:07 by tmaraval          #+#    #+#             */
/*   Updated: 2018/01/24 08:44:18 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_parser_do_parse(t_parsed_opt *opt, char *begin, char **format)
{
	ft_parser_manage_argnbr(format, begin, opt);
	ft_parser_manage_flag(format, opt);
	ft_parser_manage_width(format, opt);
	ft_parser_manage_prec(format, opt);
	ft_parser_manage_lenmod(format, opt);
}

int		ft_printf_print_until_perc(char **format)
{
	char	*begin;
	int		len;

	len = 0;
	begin = *format;
	if (!(**format) || **format == '%')
		return (0);
	while (*++begin != '%' && *begin)
		len++;
	write(1, *format, len + 1);
	*format = begin;
	return (len + 1);
}

int		ft_printf(const char *restrict format, ...)
{
	va_list			curr_arg;
	char			*p_format;
	t_parsed_opt	opt;
	int				ret;

	if (format == NULL)
		return (0);
	va_start(curr_arg, format);
	p_format = (char *)format;
	ret = 0;
	while (*p_format)
	{
		ret += ft_printf_print_until_perc(&p_format);
		if (*p_format == '%')
		{
			ft_parser_init_t_parsed_opt(&opt);
			ret += ft_parser(&opt, &p_format, curr_arg);
		}
	}
	va_end(curr_arg);
	return (ret);
}
