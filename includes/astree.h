/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 05:23:36 by cormarti          #+#    #+#             */
/*   Updated: 2018/08/14 10:38:21 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASTREE_H
# define ASTREE_H

#include "readline.h"
typedef enum e_nodetype		t_nodetype;
typedef struct s_astree		t_astree;

enum	e_nodetype
{
	NT_ROOT = -2,
	NT_PIPE = 1,
	NT_SEMI,
	NT_CMD,
	NT_AND,
	NT_OR_IF,
	NT_AND_IF,
};

struct	s_astree
{
	t_nodetype	type;
	t_nodetype	parent;
	int		root_pipe;
	t_tkn		*arg;
	t_astree	*left;
	t_astree	*right;
	int			is_root_node;
};

void		ast_debug(t_astree *astree);
t_astree	*ast_build(t_tkn *tkn);
void		ast_set_parent(t_astree *astree);
void		ast_set_rootpipe(t_astree *astree);
void		do_ast(t_tkn *tkn, t_buffer *tbuffer, char ***env);
void		do_ast_simple(t_tkn *tkn, char **env);
#endif
