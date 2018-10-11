/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_cmp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 15:22:37 by tmaraval          #+#    #+#             */
/*   Updated: 2018/10/11 11:44:21 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include "../../includes/libft.h"

t_list	*completion_cmp_userinput_filelist(char *userinput, t_list *filelist)
{
	t_list	*ret;
	t_list	*new;
	int		i;
	char	*str;

	ret = NULL;
	while (filelist)
	{
		i = 0;
		str = (char *)filelist->content;
		while (str[i] == userinput[i] && userinput[i] && str[i])
			i++;
		if (i > 0 && !(i < (int)ft_strlen(userinput)))
		{
			new = ft_lstnew(filelist->content,
			ft_strlen(filelist->content) + 1);
			ft_lstadd(&ret, new);
		}
		filelist = filelist->next;
	}
	return (ret);
}
