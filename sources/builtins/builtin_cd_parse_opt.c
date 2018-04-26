/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_parse_opt.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 10:58:27 by tmaraval          #+#    #+#             */
/*   Updated: 2018/02/02 15:54:01 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		builtin_cd_parse_setopt(char *cmd, t_cd_opt *opt)
{
	if (*cmd == 'L')
	{
		opt->l = 1;
		opt->p = 0;
	}
	if (*cmd == 'P')
	{
		opt->l = 0;
		opt->p = 1;
	}
}

int			builtin_cd_parse_opt(char *cmd, t_cd_opt *opt)
{
	opt->l = 0;
	opt->p = 0;
	if (cmd == NULL)
		return (0);
	if (*cmd && cmd[0] == '-')
	{
		cmd++;
		while (*cmd)
		{
			if (!ft_strchr("PL", *cmd))
			{
				error_print_usage("cd : [-PL] [dir]");
				return (-1);
			}
			builtin_cd_parse_setopt(cmd, opt);
			cmd++;
		}
	}
	return (0);
}
