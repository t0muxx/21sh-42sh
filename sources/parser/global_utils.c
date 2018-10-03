/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 18:36:48 by cormarti          #+#    #+#             */
/*   Updated: 2018/10/03 18:51:35 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"

char	*get_global_value(char *key, char **env)
{
	int		i;
	char	*value;

	i = 0;
	value = "";
	if ((value = env_get_var(key, env)) != NULL)
		return ("");
	while (globals[i].key != NULL)
	{
		if (ft_strcmp(globals[i].key, key) == 0)
			return (globals[i].value);
		i++;
	}
	return ("");
}

char	*get_global_key(char *value)
{
	int	i;

	i = 0;
	while (globals[i].value != NULL)
	{
		if (ft_strcmp(globals[i].value, value) == 0)
			return (globals[i].key);
	}
	return (NULL);
}

int		global_strlen(char *str, int index)
{
	int	len;

	len = 0;
	index++;
	if (!ft_isalpha(str[index]))
		return (0);
	while (str[index] != '\0' && ft_isalnum(str[index]) != 0)
	{
		len++;
		index++;
	}
	return (len);
}

char	*global_concat(char *dest, char *value, int index, int len)
{
	int	i;
	int	val_len;

	i = 0;
	val_len = ft_strlen(value);
	while (index < len && i < val_len)
	{
		dest[index] = value[i];
		index++;
		i++;
	}
	return (dest);
}
