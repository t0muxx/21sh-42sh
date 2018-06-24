/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or_if.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 03:20:55 by cormarti          #+#    #+#             */
/*   Updated: 2018/06/24 12:02:41 by tomlulu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/astree.h"
#include "../../includes/exec.h"

/* a la ligne check_exec_exception(exec)
 * on peut peut-etre simplifier ? pk appeler une autre fonction
 * qui check si le parent est un pipe et si oui return 1 
 * pour retourner 0 sur node_or_if ?????
 */

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
