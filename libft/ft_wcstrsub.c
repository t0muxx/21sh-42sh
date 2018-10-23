/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wcstrsub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 08:24:32 by tmaraval          #+#    #+#             */
/*   Updated: 2018/01/17 08:31:43 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

wchar_t		*ft_wcstrsub(wchar_t const *s, unsigned int start, size_t len)
{
	wchar_t	*s1;
	size_t	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if ((s1 = malloc(sizeof(wchar_t) * (len + 1))) == NULL)
		return (NULL);
	while (s[i] && i < len)
	{
		s1[i] = s[start + i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}
