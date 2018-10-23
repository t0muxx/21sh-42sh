/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 07:43:53 by tmaraval          #+#    #+#             */
/*   Updated: 2017/11/20 08:08:58 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_itoa_neg(int n, int cntdigit)
{
	char *ret;
	long nb;

	nb = (long)n;
	if (nb == 0)
	{
		if ((ret = (char *)malloc(sizeof(char) * 2)) == NULL)
			return (NULL);
		ret[0] = '0';
		ret[1] = '\0';
		return (ret);
	}
	if ((ret = (char *)malloc(sizeof(char) * cntdigit + 2)) == NULL)
		return (NULL);
	ret[0] = '-';
	nb = nb * -1;
	ret[cntdigit + 1] = '\0';
	while (cntdigit > 0)
	{
		ret[cntdigit] = (nb % 10) + '0';
		nb = nb / 10;
		cntdigit--;
	}
	return (ret);
}

static char		*ft_itoa_pos(int n, int cntdigit)
{
	char *ret;

	if ((ret = (char *)malloc(sizeof(char) * cntdigit + 1)) == NULL)
		return (NULL);
	ret[cntdigit] = '\0';
	while (cntdigit > 0)
	{
		ret[cntdigit - 1] = (n % 10) + '0';
		n = n / 10;
		cntdigit--;
	}
	return (ret);
}

char			*ft_itoa(int n)
{
	int		cntdigit;
	long	nb;
	char	*ret;

	nb = n;
	cntdigit = 0;
	while (nb != 0)
	{
		nb = nb / 10;
		cntdigit++;
	}
	if (n > 0)
		ret = ft_itoa_pos(n, cntdigit);
	else
		ret = ft_itoa_neg(n, cntdigit);
	return (ret);
}
