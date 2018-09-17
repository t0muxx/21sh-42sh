/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlulu <tomlulu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 12:00:15 by tomlulu           #+#    #+#             */
/*   Updated: 2018/09/17 11:07:58 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "error.h"
#include <unistd.h>
#include "readline.h"

int		builtin_unsetenv(char **cmd, char ***myenv, t_buffer *tbuffer)
{
	int i;
	int ret;

	i = 0;
	if (tbuffer)
		NULL;
	while (cmd[i])
		i++;
	if (i < 2)
	{
		error_print(TOOFEWARG, "unsetenv", "\0");
		return (-1);
	}
	i = 0;
	while (cmd[i])
	{
		ret = env_delete_var(cmd[i], myenv);
		i++;
	}
	return (ret);
}
