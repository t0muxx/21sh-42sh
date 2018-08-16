/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or_if.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 03:20:55 by cormarti          #+#    #+#             */
/*   Updated: 2018/08/16 11:00:38 by tomux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/astree.h"
#include "../../includes/exec.h"

int		node_or_if(t_astree *astree, char ***env, t_exec *exec)
{
	if (astree->left && astree->left->type == NT_CMD)
		exec->prec_exec = fork_and_exec(astree->left, env);
	if (astree->left && astree->left->type != NT_CMD)
		exec->prec_exec = fork_and_exec(astree->left->right, env);
	if (exec->prec_exec == EXIT_SUCCESS)
	{
		exec->dont = 1;
		return (EXIT_SUCCESS);
	}
	else
		return (fork_and_exec(astree->right, env));
}
