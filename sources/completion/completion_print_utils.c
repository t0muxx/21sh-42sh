/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_print_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 11:15:45 by tmaraval          #+#    #+#             */
/*   Updated: 2018/09/08 11:21:23 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>
#include <sys/types.h>
#include "libft.h"

int		completion_print_get_max_len(t_list *filelist)
{
	int max;

	max = 0;
	while (filelist)
	{
		if (max < (int)ft_strlen(filelist->content))
			max = ft_strlen(filelist->content);
		filelist = filelist->next;
	}
	return (max);
}

int		completion_print_get_word_by_cols(int maxlen)
{
	int				wordbycol;
	int				colnbr;
	struct winsize	w;

	ioctl(0, TIOCGWINSZ, &w);
	colnbr = w.ws_col;
	wordbycol = 1;
	while (((colnbr - 2) - ((maxlen + 2) * wordbycol)) > 2)
		wordbycol++;
	if (((colnbr - 2) - ((maxlen + 2) * wordbycol)) < 0)
		wordbycol--;
	return (wordbycol);
}

void	completion_print_space(int maxlen, int len)
{
	while (len < maxlen)
	{
		ft_putstr(" ");
		len++;
	}
}
