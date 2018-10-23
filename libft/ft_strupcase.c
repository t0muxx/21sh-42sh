/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strupcase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 08:33:48 by tmaraval          #+#    #+#             */
/*   Updated: 2017/11/20 08:13:09 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strupcase(char *string)
{
	int i;

	i = 0;
	while (string[i])
	{
		string[i] = ft_toupper(string[i]);
		i++;
	}
	return (string);
}
