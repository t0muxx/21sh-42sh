/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 11:19:11 by tmaraval          #+#    #+#             */
/*   Updated: 2018/10/15 10:41:12 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "readline.h"
#include "utils.h"

int		builtin_echo_write(char *towrite)
{
	if (write(1, towrite, ft_strlen(towrite)) == -1)
		return (-1);
	return (0);
}

int		builtin_echo(char **cmd)
{
	int		nopt;
	int		i;

	i = 1;
	nopt = 0;
	if (ft_2darraylen(cmd) == 1 && write(1, "\n", 1))
		return (0);
	if (**cmd && cmd[1][0] == '-' && cmd[1][1] == 'n')
	{
		i++;
		nopt = 1;
	}
	while (cmd[i])
	{
		if ((nopt == 0 && i > 1) || (nopt == 1 && i > 3))
			write(1, " ", 1);
		if (builtin_echo_write(cmd[i]) == -1)
			return (-1);
		i++;
	}
	if (nopt != 1)
		write(1, "\n", 1);
	return (0);
}
