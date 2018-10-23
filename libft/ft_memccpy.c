/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 15:24:02 by tmaraval          #+#    #+#             */
/*   Updated: 2017/11/20 08:09:38 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	const char			*s;
	char				*d;
	char				x;

	s = (const char *)src;
	d = (char *)dst;
	x = (unsigned char)c;
	while (n-- > 0)
		if ((*d++ = *s++) == x)
			return (d);
	return (NULL);
}
