/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 03:20:55 by cormarti          #+#    #+#             */
/*   Updated: 2018/08/14 09:31:00 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/astree.h"
#include "../../includes/exec.h"

int		node_semi(t_astree *astree, char ***env, t_exec *exec)
{
	if (exec->prec_exec == -2 && astree->left && astree->left->type == NT_CMD)
		fork_and_exec(astree->left, env);
	if (astree->parent == 2 && astree->right)
		fork_and_exec(astree->right, env);
	if (astree->parent == -2 && astree->right)
		fork_and_exec(astree->right, env);
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
