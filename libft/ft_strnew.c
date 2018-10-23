/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:28:07 by tmaraval          #+#    #+#             */
/*   Updated: 2017/11/20 08:12:29 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *s;

	if ((s = (char *)malloc(sizeof(char) * size + 1)) == NULL)
		return (NULL);
	ft_memset(s, 0, size + 1);
	return (s);
}
