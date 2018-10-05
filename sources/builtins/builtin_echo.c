/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 11:19:11 by tmaraval          #+#    #+#             */
/*   Updated: 2018/10/05 14:24:47 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "readline.h"
#include "utils.h"

int		builtin_echo_write(char *towrite, char **myenv)
{
	char	*var;
	char	*temp;

	if (write(1, towrite, ft_strlen(towrite)) == -1)
		return (-1);
	return (0);
}

int		builtin_echo(char **cmd, char ***myenv)
{
	int		nopt;
	int		i;

	i = 1;
	nopt = 0;
	if (ft_2darraylen(cmd) == 1 && write(1, "\n", 1))
		return (0);
	if (**cmd && cmd[1][0] == '-' && cmd[2][0] == 'n')
	{
		i = i + 2;
		nopt = 1;
	}
	while (cmd[i])
	{
		if ((nopt == 0 && i > 1) || (nopt == 1 && i > 3))
			write(1, " ", 1);
		if (builtin_echo_write(cmd[i], *myenv) == -1)
			return (-1);
		i++;
	}
	if (nopt != 1)
		write(1, "\n", 1);
	return (0);
}
