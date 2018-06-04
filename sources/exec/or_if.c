/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or_if.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 03:20:55 by cormarti          #+#    #+#             */
/*   Updated: 2018/06/04 16:38:39 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/astree.h"
#include "../../includes/exec.h"

int		node_or_if(t_astree *astree, char **env, int last_exec, t_exec *exec)
{
	if (astree->type == NT_CMD)
		return (last_exec ? 0 : fork_and_exec(astree, env));
	if (astree->left->type == NT_CMD)
		return (fork_and_exec(astree->left, env) ? 1 : 0);
	else if (astree->left->type == NT_OR_IF)
	{
		if (last_exec)
			return (1);
	}
	else if (last_exec)
		return (0);
	return (fork_and_exec(astree->left->right, env) ? 1 : 0);
}
