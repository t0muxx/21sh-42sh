/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 10:07:47 by tmaraval          #+#    #+#             */
/*   Updated: 2018/08/17 10:36:06 by tomux            ###   ########.fr       */
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

void		do_ast(t_tkn *tkn, t_buffer *tbuffer, char ***env)
{
	t_astree		*astree;

	while (tkn->next)
	{
		if (tkn->next->type == CHR_NEWLINE)
			break ;
		tkn = tkn->next;
	}
	tkn->next = NULL;
	astree = ast_build(tkn);
	term_close();
	free(tbuffer->termcap);
	ast_set_parent(astree);
	ast_set_rootpipe(astree);
	child_process(astree, env);
	free_astree(astree);
}

void		do_ast_simple(t_tkn *tkn, char **env)
{
	t_astree		*astree;

	while (tkn->next)
	{
		if (tkn->next->type == CHR_NEWLINE)
			break ;
		tkn = tkn->next;
	}
	tkn->next = NULL;
	astree = ast_build(tkn);
	ast_set_parent(astree);
	ast_set_rootpipe(astree);
	child_process(astree, &env);
	free_astree(astree);
}
