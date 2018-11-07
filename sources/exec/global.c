/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 13:44:11 by cormarti          #+#    #+#             */
/*   Updated: 2018/11/07 15:21:59 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "global.h"
#include "lexer.h"
#include "exec.h"
#include "env.h"

static char	*extract_assignment(char *str, int value)
{
	char	*dest;
	int		len;

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

void		remove_global(char *str)
{
	int		i;

	i = 0;
	while (g_globals[i].key)
	{
		if (ft_strcmp(g_globals[i].key, str) == 0)
		{
			free(g_globals[i].value);
			g_globals[i].value = ft_strdup("");
			break ;
		}
		i++;
	}
}

static int	free_on_exists(t_global new)
{
	int		i;

	i = 0;
	while (g_globals[i].key != NULL)
	{
		if (i >= GLOBAL_BUF)
			ft_putendl("max buf size reached");
		if (ft_strcmp(new.key, g_globals[i].key) == 0)
		{
			free(g_globals[i].key);
			free(g_globals[i].value);
			g_globals[i] = new;
			break ;
		}
		i++;
	}
	return (i);
}

void		insert_global(char *str, char ***env, int env_add)
{
	int			index;
	t_global	new;

	index = 0;
	new.key = extract_assignment(str, 0);
	new.value = extract_assignment(str, 1);
	if (env_update_var(new.key, new.value, *env) == 0)
	{
		if (env_add)
			env_add_var(new.key, new.value, env);
		index = free_on_exists(new);
		g_globals[index] = new;
	}
	else
	{
		free(new.value);
		free(new.key);
	}
}
