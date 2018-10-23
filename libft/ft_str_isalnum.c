/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_isalnum.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlulu <tomlulu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 11:18:39 by tomlulu           #+#    #+#             */
/*   Updated: 2018/02/08 11:21:29 by tomlulu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_str_isalnum(const char *str)
{
	char *s;

	s = (char *)str;
	while (*s)
	{
		if (ft_isalnum(*s) == 0)
			return (0);
		s++;
	}
	return (1);
}
