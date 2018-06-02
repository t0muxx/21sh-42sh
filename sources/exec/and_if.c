/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_if.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 03:20:55 by cormarti          #+#    #+#             */
/*   Updated: 2018/06/02 05:16:42 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/astree.h"
#include "../../includes/exec.h"
#include "../../includes/ext_node_fun.h"

int		node_and_if(t_astree *astree, char **env)
{
	ft_putendl("in and_if");
	if (astree->left->type == NT_CMD)
	{
		exec_cmd(astree->left, env);
		ft_putstr("yo");
		return (1);
	}
	else
	{
		ft_putendl("not last node");
		if (exec_cmd(astree->left->right, env))
			return (1);
		else
		{
			ft_putstr(astree->left->right->arg[0]->data);
			ft_putendl(" failed to execute, exit");
			return (0);
		}
	}
}
