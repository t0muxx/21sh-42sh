/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 13:55:39 by tmaraval          #+#    #+#             */
/*   Updated: 2017/11/20 08:12:20 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t i;

	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		if ((dst[i] = src[i]) == 0)
		{
			while (i < len)
			{
				dst[i] = '\0';
				i++;
			}
		}
		i++;
	}
	return (dst);
}
