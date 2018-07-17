/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 03:20:55 by cormarti          #+#    #+#             */
/*   Updated: 2018/06/04 16:36:58 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/astree.h"
#include "../../includes/exec.h"
#include "../../includes/ext_node_fun.h"

int		node_and(t_astree *astree, char **env, int last_exec, t_exec *exec)
{
	if (astree->left && astree->left->type == NT_CMD)
	       exec->last_exec = fork_and_exec(astree->left, env);
	if (check_exec_exception(exec))
		return (0);
	if (exec->last_exec == 0)
		return (0);
	else
		return (fork_and_exec(astree->right, env));
}
