/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 18:22:12 by tmaraval          #+#    #+#             */
/*   Updated: 2017/11/20 08:12:37 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*ret;

	i = 0;
	while (s[i] != '\0')
		i++;
	ret = (char *)s;
	while (i >= 0)
	{
		if (s[i] == c)
		{
			return (&ret[i]);
		}
		i--;
	}
	return (NULL);
}
