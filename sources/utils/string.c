/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 09:07:01 by tmaraval          #+#    #+#             */
/*   Updated: 2018/09/05 14:58:55 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "readline.h"

/*
** string_shift_right shift a string from pos
** to the left.
** like : before : [t][e][s][t]
** 	   after  : [t][ ][e][s][t]
*/

char	*extract_current_word(char *str, int pos)
{
	int start;
	int len;
	int i;
	char *ret;

	start = pos;
	len = 0;
	while (start >= 0 && str[start] != ' ')
		start--;
	i = start + 1;
	while (str[i] && str[i] != ' ')
	{
		len++;
		i++;
	}
	ret = ft_strsub(str, start + 1, len);
	return (ret);
}

char	*string_concat_array(char **array)
{
	int		i;
	char	*ret;
	char	*tmp;

	i = 0;
	ret = ft_strdup(array[i]);
	i++;
	while (array[i])
	{
		tmp = ret;
		ret = ft_strjoin(ret, array[i]);
		free(tmp);
		i++;
	}
	return (ret);
}

void	string_shift_right(char **str, int pos)
{
	int		i;

	i = (int)ft_strlen(*str);
	while (str != NULL && i >= pos)
	{
		str[0][i + 1] = str[0][i];
		i--;
	}
	str[0][i + 1] = ' ';
}

void	string_delete_char(char **str, int pos)
{
	int		i;

	i = (int)ft_strlen(*str);
	while (str != NULL && pos < i)
	{
		str[0][pos] = str[0][pos + 1];
		pos++;
	}
	str[0][pos] = 0;
}

int		ft_putcc(int c)
{
	write(1, &c, 1);
	return (0);
}
