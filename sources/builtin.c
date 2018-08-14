/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 14:13:48 by tmaraval          #+#    #+#             */
/*   Updated: 2018/08/14 10:50:07 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int		builtin_check_builtin(char **cmd, char ***myenv)
{
	int			i;
	t_builtin	builtin[BUILTINNBR];

	builtin_get_builtin(builtin);
	i = 0;
	while (i < BUILTINNBR)
	{
		if (ft_strcmp(builtin[i].name, cmd[0]) == 0)
		{
			builtin[i].addr(cmd, myenv);
			return (1);
		}
		i++;
	}
	return (0);
}

void	builtin_get_builtin(t_builtin *builtin)
{
	builtin[0].name = "echo";
	builtin[0].addr = &builtin_echo;
	builtin[1].name = "cd";
	builtin[1].addr = &builtin_cd;
	builtin[2].name = "setenv";
	builtin[2].addr = &builtin_setenv;
	builtin[3].name = "unsetenv";
	builtin[3].addr = &builtin_unsetenv;
	builtin[4].name = "env";
	builtin[4].addr = &builtin_env;
	builtin[5].name = "exit";
	builtin[5].addr = &builtin_exit;
}
