/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 09:35:38 by tmaraval          #+#    #+#             */
/*   Updated: 2018/10/11 09:41:47 by tomux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "builtin.h"
#include "utils.h"

int		builtin_env_err(char **cmd)
{
	write(2, "Illegal option -- ", 18);
	write(2, &cmd[1][1], 1);
	write(2, "\n", 1);
	error_print_usage("env [-i] [name=value] [utility [argument]]");
	return (-1);
}

int		builtin_env_check_i(char **cmd)
{
	int iopt;
	int i;

	i = 1;
	iopt = 0;
	if (cmd[i][0] != '-')
		return (0);
	if (ft_strcmp(cmd[i], "-i"))
		return (builtin_env_err(cmd));
	else
	{
		iopt = 1;
		i++;
	}
	return (iopt);
}

char	**builtin_env_malloc_env(char **cmd, int *i)
{
	char	**newenv;

	if ((builtin_env_check_i(cmd)) == 1)
	{
		(*i)++;
		if (!(newenv = (char **)malloc(sizeof(char *) * 1)))
			error_malloc_err(1, (void **)cmd);
		newenv[0] = 0;
	}
	else
		newenv = env_create_copy();
	return (newenv);
}

char	**builtin_env_get_env(char **cmd, int *i)
{
	int		iopt;
	char	**var;
	char	**newenv;

	*i = 1;
	if ((newenv = builtin_env_malloc_env(cmd, i)) == NULL)
		error_malloc_err(1, (void **)cmd);
	while (cmd[*i] && ft_strchr(cmd[*i], '='))
	{
		var = ft_strsplit(cmd[*i], '=');
		if (var[1] == NULL)
			return (NULL);
		if ((iopt = builtin_env_check_i(cmd)) == 0)
		{
			if (env_update_var(var[0], var[1], newenv) == 0)
				newenv = env_add_var(var[0], var[1], &newenv);
		}
		else
			newenv = env_add_var(var[0], var[1], &newenv);
		utils_free_2darray((void **)var);
		(*i)++;
	}
	return (newenv);
}

int		builtin_env(char **cmd, char ***myenv)
{
	int		i;

	i = 0;
	while (cmd[i])
		i++;
	if (i == 1)
		env_print(*myenv);
	else
		return (builtin_env_do(cmd, &i, *myenv));
	if (cmd)
		NULL;
	return (0);
}
