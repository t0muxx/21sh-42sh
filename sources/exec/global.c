/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 13:44:11 by cormarti          #+#    #+#             */
/*   Updated: 2018/10/02 14:56:25 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "global.h"
#include "lexer.h"
#include "exec.h"


static char	*extract_assignment(char *str, int value)
{
	char	*dest;
	int	len;

	len = 0;
	if (value)
	{
		while (str[len] != '=' && str[len] != '\0')
			len++;
		str += ++len;
		len = ft_strlen(str);
	}
	else
	{
		while (str[len] != '=' && str[len] != '\0')
			len++;
	}
	if (!(dest = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	dest[len] = '\0';
	ft_strncpy(dest, str, len);
	return (dest);


}

char	*get_global_value(char *key, char **env)
{
	int		i;
	char	*value;

	i = 0;
	value = "";
	if ((value = env_get_var(key, env)) != NULL)
		return (value);	
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

void		remove_global(char *str)
{
	int		i;

	i = 0;
	while (globals[i].key)
	{
		if (ft_strcmp(globals[i].key, str) == 0)
		{
			free(globals[i].value);
			globals[i].value = ft_strdup("");
			break ;
		}
		i++;
	}
}

void		insert_global(char *str, char ***env)
{
	int		i;
	t_global	new;

	i = 0;
	new.key = extract_assignment(str, 0);
	new.value = extract_assignment(str, 1);
	if (env_update_var(new.key, new.value, *env) == 0)
	{
		while (globals[i].key != NULL)
		{
			if (i >= GLOBAL_BUF)
				ft_putendl("max buf size reached");
				//func to realloc more on global array, and copy all globals in the new array)
			if (ft_strcmp(new.key, globals[i].key) == 0)
			{
				free(globals[i].key);
				free(globals[i].value);
				globals[i] = new;
				break ;
			}
			i++;
		}
		globals[i] = new;
	}
	else
	{
		free(new.value);
		free(new.key);
	}
}

