/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or_if.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 03:20:55 by cormarti          #+#    #+#             */
/*   Updated: 2018/06/23 01:48:49 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/astree.h"
#include "../../includes/exec.h"

int		node_or_if(t_astree *astree, char **env, t_exec *exec)
{
	if (astree->left->type == NT_CMD)
		exec->last_exec = fork_and_exec(astree->left, env);
	if (check_exec_exception(exec))
		return (0);
	if (exec->last_exec)
	{
		if (exec->parent == NT_AND_IF
			|| (astree->left->type == NT_OR_IF && exec->parent == NT_OR_IF))
			return (1);
		return (0);
	}
	else
		return (fork_and_exec(astree->right, env));
}
