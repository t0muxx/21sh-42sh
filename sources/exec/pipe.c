/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 03:20:55 by cormarti          #+#    #+#             */
/*   Updated: 2018/06/05 15:45:55 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/astree.h"
#include "../../includes/exec.h"
#include "../../includes/ext_node_fun.h"
#include "utils.h"

int		node_pipe(t_astree *astree, char **env, int last_exec, t_exec *exec)
{
	int	pipefd[2];
	int	pipefd2[2];
	pid_t pid;
	pid_t pid2;
	char	**cmd;

/*	if (exec->parent == -9999)
	{
		cmd = lst_arr(astree->right->arg, env);
		ft_printf("last node cmd = |%s|\n", cmd[0]);
	}
	else
	{*/
		cmd = lst_arr(astree->left->arg, env);
		ft_printf("node cmd = |%s|\n", cmd[0]);
		cmd = lst_arr(astree->right->arg, env);
		ft_printf("node cmd = |%s|\n", cmd[0]);
		exit(EXIT_SUCCESS);
	//}
	return (0);
}
