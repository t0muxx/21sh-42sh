/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 10:10:40 by tmaraval          #+#    #+#             */
/*   Updated: 2017/12/19 13:59:15 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*newchaine;
	int		len;

	len = ft_strlen(s1) + 1;
	if ((newchaine = (char *)malloc(sizeof(char) * len)) == NULL)
		return (NULL);
	ft_memcpy(newchaine, s1, len);
	return (newchaine);
}
