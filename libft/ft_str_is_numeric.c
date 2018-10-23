/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_numeric.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 09:02:09 by tmaraval          #+#    #+#             */
/*   Updated: 2017/11/17 09:14:21 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_str_is_numeric(const char *s)
{
	char *str;

	str = (char *)s;
	if (!str)
		return (0);
	while (*str)
	{
		if (ft_isdigit(*str) != 1)
			return (0);
		str++;
	}
	return (1);
}
