/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 14:13:48 by tmaraval          #+#    #+#             */
/*   Updated: 2018/10/23 15:11:54 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "exec.h"

int		builtin_check_builtin(t_astree *astree, char **cmd, char ***myenv)
{
	int			i;
	t_builtin	builtin[BUILTINNBR];
	int			saved_stdout;
	int			saved_stdin;

	saved_stdout = 0;
	builtin_get_builtin(builtin);
	i = -1;
	while (i++ < BUILTINNBR)
	{
		if (ft_strcmp(builtin[i].name, cmd[0]) == 0)
		{
			saved_stdout = dup(STDOUT_FILENO);
			saved_stdin = dup(STDIN_FILENO);
			if (astree)
				redirect_cmd(astree->arg);
			builtin[i].addr(cmd, myenv);
			dup2(saved_stdout, STDOUT_FILENO);
			dup2(saved_stdin, STDIN_FILENO);
			close(saved_stdout);
			close(saved_stdin);
			return (1);
		}
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
