/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 05:23:36 by cormarti          #+#    #+#             */
/*   Updated: 2018/07/25 23:31:31 by tomux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASTREE_H
# define ASTREE_H

typedef enum e_nodetype		t_nodetype;
typedef struct s_astree		t_astree;

enum	e_nodetype
{
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

#endif
