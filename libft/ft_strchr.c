/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 17:58:38 by tmaraval          #+#    #+#             */
/*   Updated: 2017/11/20 08:10:38 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*ret;

	i = 0;
	ret = (char *)s;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (&ret[i]);
		i++;
	}
	if (s[i] == c)
		return (&ret[i]);
	return (NULL);
}
