/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 08:21:11 by tmaraval          #+#    #+#             */
/*   Updated: 2017/11/20 08:13:03 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_skip_space(char const *s)
{
	int stt;

	stt = 0;
	while (s[stt] && (s[stt] == ' ' || s[stt] == '\t' || s[stt] == '\n'))
		stt++;
	return (stt);
}

char		*ft_strtrim(char const *s)
{
	size_t	stt;
	size_t	end;
	int		i;
	char	*ret;

	if (s == NULL)
		return (NULL);
	i = -1;
	end = ft_strlen(s) - 1;
	stt = ft_skip_space(s);
	if (stt == end + 1)
	{
		if ((ret = (char *)malloc(sizeof(char) * 1)) == NULL)
			return (NULL);
		*ret = '\0';
		return (ret);
	}
	while (end > 0 && (s[end] == ' ' || s[end] == '\t' || s[end] == '\n'))
		end--;
	if ((ret = (char *)malloc(sizeof(char) * (end - stt) + 2)) == NULL)
		return (NULL);
	while (stt + ++i <= end)
		ret[i] = s[stt + i];
	ret[i] = '\0';
	return (ret);
}
