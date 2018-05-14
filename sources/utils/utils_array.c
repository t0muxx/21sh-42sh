/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlulu <tomlulu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 07:36:24 by tomlulu           #+#    #+#             */
/*   Updated: 2018/02/14 10:59:45 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	utils_free_2darray(void **array)
{
	int i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	utils_delete_in_2darray(char **tab, int index)
{
	int		tabnbr;
	char	*temp;

	tabnbr = 0;
	while (tab[tabnbr])
		tabnbr++;
	temp = tab[index];
	while (index + 1 < tabnbr)
	{
		tab[index] = tab[index + 1];
		index++;
	}
	tab[index] = 0;
	free(temp);
}

int		utils_str_is_empty(const char *str)
{
	char *s;

	s = (char *)str;
	while (*s)
	{
		if (*s != '\t' || *s != ' ' || *s != 9)
			return (0);
		s++;
	}
	return (1);
}
