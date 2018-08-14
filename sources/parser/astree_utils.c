/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 10:07:47 by tmaraval          #+#    #+#             */
/*   Updated: 2018/08/14 10:11:49 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "lexer.h"
#include "astree.h"
#include "exec.h"
#include "env.h"

void		ast_set_parent(t_astree *astree)
{
	t_nodetype tmp;

	tmp = -2;
	while (astree)
	{
		astree->parent = tmp;
		tmp = astree->type;
		astree = astree->left;
	}
}

void		ast_set_rootpipe(t_astree *astree)
{
	int rootpipe;

	rootpipe = 1;
	while (astree)
	{
		rootpipe = 1;
		while (astree && astree->type != NT_PIPE)
		{
			astree = astree->left;
		}
		while (astree && astree->type == NT_PIPE)
		{
			astree->root_pipe = rootpipe;
			rootpipe = 0;
			astree = astree->left;
		}

	}
}
