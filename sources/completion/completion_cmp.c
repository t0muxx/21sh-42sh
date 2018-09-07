/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_cmp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 15:22:37 by tmaraval          #+#    #+#             */
/*   Updated: 2018/09/07 16:29:15 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include "../../includes/libft.h"

t_list *completion_cmp_userinput_filelist(char *userinput, t_list *filelist)
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
			new = ft_lstnew(filelist->content, ft_strlen(filelist->content) + 1);
			ft_lstadd(&ret, new);
		}
		filelist = filelist->next;
	}
	return (ret);
}

/*int		main(int argc, char **argv)
{
	t_list list1;
	t_list list2;
	t_list list3;
	t_list list4;
	t_list *ret;

	list1.content = "abcd";
	list1.next = &list2;
	list2.content = "accd";
	list2.next = &list3;
	list3.content = "abcz";
	list3.next = &list4;
	list4.content = "zbcd";
	list4.next = NULL;
	ret = completion_cmp_userinput_filelist(argv[1], &list1);
	while (ret)
	{
		ft_putendl((char *)ret->content);
		ret = ret->next;
	}
	return (0);
}*/
