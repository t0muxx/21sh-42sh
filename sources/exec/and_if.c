/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_if.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 03:20:55 by cormarti          #+#    #+#             */
/*   Updated: 2018/06/25 09:59:02 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/astree.h"
#include "../../includes/exec.h"

int		node_and_if(t_astree *astree, char **env, t_exec *exec)
{
	if (astree->left && astree->left->type == NT_CMD)
		exec->last_exec = fork_and_exec(astree->left, env);
	if (!exec->last_exec || check_exec_exception(exec))
		return (0);
	else
		return (fork_and_exec(astree->right, env));
}
