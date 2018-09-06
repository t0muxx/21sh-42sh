/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_print.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 08:30:14 by tmaraval          #+#    #+#             */
/*   Updated: 2018/09/06 09:55:56 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <sys/ioctl.h>
#include <sys/types.h>

int		completion_print_get_max_len(t_list *filelist)
{
	int max;

	max = 0;
	while (filelist)
	{
		if (max < (int )ft_strlen(filelist->content))
			max = ft_strlen(filelist->content);
		filelist = filelist->next;
	}
	return (max);
}

/*
 * tant que ((maxlen + 2) * x) - colnbr) > 3
 * x++
 *
*/
int		completion_print_get_word_by_cols(int maxlen)
{
	int	wordbycol;
	int colnbr;
	
	colnbr = tgetnum("co");
	wordbycol = 1;
	while (colnbr - ((maxlen + 2) * wordbycol) > 2)
		wordbycol++;	
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

void	completion_print(t_list *filelist)
{
	int wordbycol;
	int	maxlen;
	int i;

	i = 0;
	maxlen = completion_print_get_max_len(filelist);
	wordbycol = completion_print_get_word_by_cols(maxlen);
	while (filelist)
	{
		i = 0;
		while (filelist && i < wordbycol - 1)
		{
			ft_printf("%s", filelist->content);
			completion_print_space(maxlen, (int)ft_strlen(filelist->content));
			ft_putstr("  ");
			i++;
			filelist = filelist->next;
		}
		ft_printf("%s", filelist->content);
		ft_putendl("");
		if (filelist != NULL)
			filelist = filelist->next;
	}	
}
