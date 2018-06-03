/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_if.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 03:20:55 by cormarti          #+#    #+#             */
/*   Updated: 2018/06/03 21:08:20 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/astree.h"
#include "../../includes/exec.h"
#include "../../includes/ext_node_fun.h"

int		node_and_if(t_astree *astree, char **env, int last_exec)
{
	(void)last_exec;
	if (astree->left->type == NT_CMD)
		return (fork_and_exec(astree->left, env) ? 1 : 0);
	else
		return (fork_and_exec(astree->left->right, env) ? 1 : 0);
}
