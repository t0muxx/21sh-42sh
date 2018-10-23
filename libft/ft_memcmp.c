/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 11:14:00 by tmaraval          #+#    #+#             */
/*   Updated: 2017/11/20 08:09:51 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t		i;
	const char	*ss1;
	const char	*ss2;

	i = 0;
	ss1 = (const char*)s1;
	ss2 = (const char*)s2;
	while (i < n)
	{
		if (ss1[i] != ss2[i])
			return ((unsigned char)ss1[i] - (unsigned char)ss2[i] + 0);
		i++;
	}
	return (0);
}
