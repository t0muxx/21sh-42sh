/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 10:34:49 by tmaraval          #+#    #+#             */
/*   Updated: 2017/11/20 08:09:41 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char		*src;
	char			ch;
	size_t			i;

	i = 0;
	src = (const char *)s;
	ch = (unsigned char)c;
	while (i < n)
	{
		if (src[i] == ch)
			return ((void *)&src[i]);
		i++;
	}
	return (NULL);
}
