/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 13:57:04 by tmaraval          #+#    #+#             */
/*   Updated: 2018/05/14 10:06:54 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"

int		cd_parse_opt(char **cmd)
{
	int i;
	int j;
	int ret;

	ret = 0;
	i = 1;
	while (cmd[i])
	{
		j = 0;
		if (cmd[i][0] != '-')
			return (ret);
		else
		{
			j++;
			while (cmd[i][j])
			{
				if (cmd[i][j] == 'P')
				{
					ret = 1;
				}
				else if (cmd[i][j] == 'L')
					ret = 2;
				else
				{
					write(2, "cd: -", 5);
					write(2, &cmd[i][j], 1);
					write(2, " invalid option\n", 16);
					error_print_usage("cd [-L|-P] [dir]\n");
					return (-1);
				}
				j++;
			}
		}
		i++;
	}
	return (ret);
}

int		builtin_cd(char **cmd, char ***myenv)
{
	return (0);
}

int		main(int argc, char **argv)
{
	printf("%d\n", cd_parse_opt(argv + 1));
}
