/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_if.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 03:20:55 by cormarti          #+#    #+#             */
/*   Updated: 2018/09/20 12:53:48 by tomux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/astree.h"
#include "../../includes/exec.h"

int		node_and_if(t_astree *astree, char ***env, t_exec *exec)
{
	if (astree->left && astree->left->type == NT_CMD)
		exec->prec_exec = fork_and_exec(astree->left, env);
	if (astree->left && astree->left->type == NT_SEMI)
		exec->prec_exec = fork_and_exec(astree->left->right, env);
	if (exec->prec_exec != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	else if (astree->parent != NT_PIPE)
		return (fork_and_exec(astree->right, env));
	else
		return (exec->prec_exec);
}
