/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 08:24:25 by tmaraval          #+#    #+#             */
/*   Updated: 2018/10/15 11:11:55 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		env_until_equal(char *var)
{
	int i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	return (i);
}

char	*env_get_var(char *name, char **myenv)
{
	int			i;
	char		*temp;

	i = -1;
	if (name == NULL)
		return (NULL);
	while (myenv[i++])
	{
		temp = ft_strsub(myenv[i], 0, env_until_equal(myenv[i]));
		if (temp && ft_strcmp(temp, name) == 0
		&& ft_strlen(temp) == ft_strlen(name))
		{
			free(temp);
			temp = ft_strsub(myenv[i], ft_strlen(name) + 1,
			(ft_strlen(myenv[i]) - (ft_strlen(name) + 1)));
			if (ft_strlen(temp) == 0)
			{
				free(temp);
				return (NULL);
			}
			return (temp);
		}
		free(temp);
	}
	return (NULL);
}
