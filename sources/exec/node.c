/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 02:36:01 by cormarti          #+#    #+#             */
/*   Updated: 2018/06/03 21:10:38 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/astree.h"
#include "../../includes/exec.h"

int		node_ret(t_astree *astree)
{
	if (astree->type == NT_AND_IF
		|| astree->type == NT_PIPE)	
		return (0);
	else
		return (1);
}

int				exec_node(t_astree *astree, char **env)
{
	int		i;
	int		last_exec;

	i = 0;
	last_exec = 1;
	if (astree->left->type != NT_CMD)
	{
		last_exec = exec_node(astree->left, env);
	}
	while (node_fun[i].type)
	{
		if (node_fun[i].type == astree->type)
			return (node_fun[i].fun(astree, env, last_exec));
		i++;
	}
	return (0);
}
