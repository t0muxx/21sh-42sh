/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 13:40:09 by tmaraval          #+#    #+#             */
/*   Updated: 2017/11/20 08:09:55 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char *c;
	char *b;

	c = (char *)src;
	b = (char *)dst;
	while (n > 0)
	{
		*b++ = *c++;
		n--;
	}
	return (dst);
}
