/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_date.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlulu <tomlulu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 19:07:48 by tomlulu           #+#    #+#             */
/*   Updated: 2018/02/14 08:11:05 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_ft_date		ft_conv_date(const char *str)
{
	t_ft_date	date;
	char		**splited;
	int			i;

	i = 0;
	splited = ft_strsplit(str, ' ');
	ft_strcpy(date.day, splited[0]);
	ft_strcpy(date.month, splited[1]);
	ft_strcpy(date.daynbr, splited[2]);
	ft_strncpy(date.hour, splited[3], 5);
	date.hour[5] = '\0';
	ft_strncpy(date.year, splited[4], 5);
	if (date.year[4] == '\n')
		date.year[4] = '\0';
	while (splited[i] != 0)
	{
		free(splited[i]);
		i++;
	}
	free(splited);
	splited = NULL;
	return (date);
}

void			ft_date(t_ft_date *date)
{
	time_t ft_time;

	ft_time = time(NULL);
	*date = ft_conv_date(ctime(&ft_time));
}
