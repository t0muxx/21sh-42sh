/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 11:19:11 by tmaraval          #+#    #+#             */
/*   Updated: 2018/08/14 09:17:55 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

int		builtin_echo_write(char *towrite, char **myenv)
{
	char	*var;
	char	*temp;

	if (towrite[0] == '$')
	{
		temp = ft_strsub(towrite, 1, ft_strlen(towrite));
		var = env_get_var(temp, myenv);
		if (var != NULL && write(1, var, ft_strlen(var)) == -1)
			return (-1);
		free(temp);
		free(var);
	}
	else
	{
		if (write(1, towrite, ft_strlen(towrite)) == -1)
			return (-1);
	}
	return (0);
}

int		builtin_echo(char **cmd, char ***myenv)
{
	int		nopt;
	int		i;

	i = 1;
	nopt = 0;
	if (ft_2darraylen(cmd) == 1)
	{
		write(1, "\n", 1);
		return (0);
	}
	if (**cmd && ft_strcmp(cmd[i], "-n") == 0)
	{
		i++;
		nopt = 1;
	}
	while (cmd[i])
	{
		if (builtin_echo_write(cmd[i], *myenv) == -1)
			return (-1);
		i++;
	}
	if (nopt != 1)
		write(1, "\n", 1);
	return (0);
}
