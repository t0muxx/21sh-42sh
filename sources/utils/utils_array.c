/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlulu <tomlulu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 07:36:24 by tomlulu           #+#    #+#             */
/*   Updated: 2018/08/14 10:49:48 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	utils_free_cmd_hist(t_cmd_hist **head)
{
	t_cmd_hist *curr;

	while ((curr = *head) != NULL)
	{
		*head = (*head)->oldest;
		free(curr->cmd);
		free(curr);
	}
}

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

void	utils_delete_in_2darray(char **tabb, int index)
{
	int		tabnbr;
	char	*temp;

	tabnbr = 0;
	while (tabb[tabnbr])
		tabnbr++;
	temp = tabb[index];
	while (index + 1 < tabnbr)
	{
		tabb[index] = tabb[index + 1];
		index++;
	}
	tabb[index] = 0;
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
