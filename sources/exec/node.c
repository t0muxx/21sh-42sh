/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 02:36:01 by cormarti          #+#    #+#             */
/*   Updated: 2018/06/02 04:59:03 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/astree.h"
#include "../../includes/exec.h"

int		exec_node(t_astree *astree, char **env)
{
	int		i;

	i = 0;
	if (astree->left->type != NT_CMD)
		exec_node(astree->left, env);
	while (node_fun[i].type)
	{
		if (node_fun[i].type == astree->type)
			return (node_fun[i].fun(astree, env));
		i++;
	}
	return (0);
}
