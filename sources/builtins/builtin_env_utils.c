/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 10:58:51 by tmaraval          #+#    #+#             */
/*   Updated: 2018/08/14 11:57:36 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "builtin.h"
#include "utils.h"

int		builtin_env_do_builtin(char **cmd, char **env)
{
	t_builtin	bltin[6];

	builtin_get_builtin(bltin);
	if (builtin_check_builtin(cmd, &env) == 1)
		return (1);
	return (0);
}

int		builtin_env_do_ret(int ret, char *cmd)
{
	if (ret == EXISTERR)
	{
		error_print(EXISTERR, "env", cmd);
		return (127);
	}
	if (ret == PERMERR)
	{
		error_print(PERMERR, "env", cmd);
		return (126);
	}
	return (0);
}

int		builtin_env_do(char **cmd, int *i)
{
	char	**newenv;
	int		ret;

	if ((newenv = builtin_env_get_env(cmd, i)) == NULL)
		return (125);
	if (cmd[*i] == NULL)
	{
		env_print(newenv);
		utils_free_2darray((void **)newenv);
		return (0);
	}
	if (builtin_env_do_builtin(cmd + (*i), newenv) == 1)
	{
		utils_free_2darray((void **)newenv);
		return (0);
	}
	utils_free_2darray((void **)newenv);
	return (builtin_env_do_ret(ret, cmd[*i]));
}
