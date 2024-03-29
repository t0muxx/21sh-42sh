/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 12:14:31 by tmaraval          #+#    #+#             */
/*   Updated: 2018/11/07 14:48:45 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "env.h"
#include "builtin.h"

void	builtin_setenv_do(char **cmd, char ***myenv)
{
	if (cmd[1] != NULL)
	{
		if (cmd[2] != NULL)
		{
			if (env_update_var(cmd[1], cmd[2], *myenv) == 0)
				env_add_var(cmd[1], cmd[2], myenv);
		}
		else
		{
			if (env_update_var(cmd[1], "\0", *myenv) == 0)
				env_add_var(cmd[1], "\0", myenv);
		}
	}
}

int		builtin_setenv(char **cmd, char ***myenv)
{
	if (cmd[1] == NULL)
		env_print(*myenv);
	else
	{
		if ((ft_2darraylen(cmd)) > 3)
		{
			error_print(TOMANYARG, "setenv", "\0");
			return (-1);
		}
		if (ft_str_isalnum(cmd[1]) == 0)
		{
			error_print(ALNUMERR, "setenv", "\0");
			return (-1);
		}
		builtin_setenv_do(cmd, myenv);
	}
	return (0);
}
