/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespace.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 07:49:08 by tmaraval          #+#    #+#             */
/*   Updated: 2018/02/13 08:48:00 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_cnt_letter(const char *str)
{
	int i;

	i = 0;
	while (str[i] && ft_strchr(SEPARATOR_WHITESPACE, str[i]) == NULL)
		i++;
	return (i);
}

char		**ft_conv_list_to_array(t_list *words)
{
	int			nbword;
	t_list		*head;
	char		**ret;
	int			i;

	i = 0;
	nbword = 0;
	head = words;
	while (words != NULL)
	{
		nbword++;
		words = words->next;
	}
	if ((ret = malloc(sizeof(char *) * (nbword + 1))) == NULL)
		return (NULL);
	words = head;
	while (i < nbword)
	{
		ret[i] = ft_strdup(words->content);
		words = words->next;
		i++;
	}
	ret[i] = 0;
	ft_lst_free(head);
	return (ret);
}

char		**ft_split_whitespace(const char *str)
{
	char	*s;
	char	*temp;
	t_list	*first;
	t_list	*new;

	first = NULL;
	if (str == NULL)
		return (NULL);
	s = (char *)str;
	while (*s)
	{
		while (ft_strchr(SEPARATOR_WHITESPACE, *s) != NULL && *s != '\0')
			s++;
		if (ft_strchr(SEPARATOR_WHITESPACE, *s) == NULL && *s != '\0')
		{
			temp = ft_strsub(s, 0, ft_cnt_letter(s));
			new = ft_lstnew(temp, ft_strlen(temp) + 1);
			ft_lst_append(&first, new);
			s = s + ft_cnt_letter(s);
			free(temp);
		}
	}
	return (ft_conv_list_to_array(first));
}
