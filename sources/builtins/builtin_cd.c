/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 13:57:04 by tmaraval          #+#    #+#             */
/*   Updated: 2018/04/26 16:23:45 by tmaraval         ###   ########.fr       */
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
	j = 0;
	i = 1;
	while (cmd[i])
	{
		if (cmd[i][0] != '-')
			return (0);
		else
		{
			j++;
			if (cmd[i][j] == 'P')
			{
				ret = 1;
				j++;
			}
			else if (cmd[i][j] == 'L')
			{
				ret = 2;
				j++;
			}
			else
			{
				ft_putstr("error\n");
				return (-1);
			}
		}
		i++;
	}
	return (ret);
}

int		builtin_cd(char **cmd, char ***myenv)
{

}
