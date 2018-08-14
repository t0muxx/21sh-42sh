/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_opt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlulu <tomlulu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/28 16:47:14 by tomlulu           #+#    #+#             */
/*   Updated: 2018/08/14 10:41:53 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int		cd_skip_opt(char **cmd)
{
	int i;

	i = 1;
	while (cmd[i])
	{
		if (!ft_strcmp(cmd[i], "-"))
			return (i);
		else if (!ft_strcmp(cmd[i], "--"))
			return (i + 1);
		else if (cmd[i][0] != '-')
			return (i);
		else
			;
		i++;
	}
	return (i);
}

int		cd_check_opt(char *opt)
{
	int ret;

	ret = 0;
	if (!ft_strcmp(opt, "-P"))
		ret = CD_P;
	else if (!ft_strcmp(opt, "-L"))
		ret = CD_L;
	else if (!ft_strcmp(opt, "--"))
		;
	else if (!ft_strcmp(opt, "-"))
		;
	else
	{
		write(2, "cd : ", 5);
		error_invalid_opt(opt);
		write(2, "cd : ", 5);
		error_print_usage("cd [-L|-P] [dir]");
		return (CD_OPTERR);
	}
	return (ret);
}

int		cd_parse_opt(char **cmd)
{
	int i;
	int ret;

	ret = 0;
	i = 1;
	while (cmd[i] && cmd[i][0] == '-')
	{
		if ((ft_strcmp(cmd[i], "-")) && ft_strcmp(cmd[i], "--"))
			ret = cd_check_opt(cmd[i]);
		if (ret == CD_OPTERR)
			return (-1);
		if (!ft_strcmp(cmd[i], "--"))
			break ;
		i++;
	}
	return (ret);
}
