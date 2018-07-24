/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 03:20:55 by cormarti          #+#    #+#             */
/*   Updated: 2018/07/23 22:01:51 by tomux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/astree.h"
#include "../../includes/exec.h"
#include "../../includes/ext_node_fun.h"

int		node_and(t_astree *astree, char **env, int last_exec, t_exec *exec)
{
	/* if (astree->left && astree->left->type == NT_CMD)
	       exec->last_exec = fork_and_exec(astree->left, env);
	if (check_exec_exception(exec))
		return (0);
	if (exec->last_exec == 0)
		return (0);
	else
		return (child_process(astree->right, env));*/
	dprintf(2, "node and |%d|\n", exec->last_exec);
}
