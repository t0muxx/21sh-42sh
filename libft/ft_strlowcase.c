/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlowcase.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 08:54:38 by tmaraval          #+#    #+#             */
/*   Updated: 2017/11/20 08:11:29 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strlowcase(char *string)
{
	int i;

	i = 0;
	while (string[i])
	{
		string[i] = ft_tolower(string[i]);
		i++;
	}
	return (string);
}
