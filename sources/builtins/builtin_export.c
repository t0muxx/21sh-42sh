/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 12:14:31 by tmaraval          #+#    #+#             */
/*   Updated: 2018/11/07 15:37:48 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "env.h"
#include "builtin.h"

void	builtin_export_do(char **cmd, char ***myenv)
{
	char	*value;
	int		i;

	i = 1;
	value = NULL;
	while (cmd[i] != NULL)
	{
		if (ft_strchr(cmd[i], '='))
			insert_global(cmd[i], myenv, 1);
		else
		{
			value = get_global_value(cmd[i], *myenv);
			if (ft_strlen(value) > 0)
			{
				if (env_update_var(cmd[i], value, *myenv) == 0)
					env_add_var(cmd[i], value, myenv);
			}
			if (ft_strlen(value) != 0)
				free(value);
		}
		i++;
	}
}

int		builtin_export(char **cmd, char ***myenv)
{
	if (cmd[1] == NULL)
		env_print(*myenv);
	else
		builtin_export_do(cmd, myenv);
	return (0);
}
