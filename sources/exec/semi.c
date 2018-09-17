/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 03:20:55 by cormarti          #+#    #+#             */
/*   Updated: 2018/09/17 11:10:59 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/astree.h"
#include "../../includes/exec.h"

int		node_semi(t_astree *astree, char ***env, t_exec *exec)
{
	if (exec->prec_exec == -2 && astree->left && astree->left->type == NT_CMD)
		fork_and_exec(astree->left, env, exec->tbuffer);
	if (astree->parent == 2 && astree->right)
		fork_and_exec(astree->right, env, exec->tbuffer);
	if (astree->parent == -2 && astree->right)
		fork_and_exec(astree->right, env, exec->tbuffer);
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
