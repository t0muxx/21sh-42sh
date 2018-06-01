/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 05:23:36 by cormarti          #+#    #+#             */
/*   Updated: 2018/06/01 02:28:26 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASTREE_H
# define ASTREE_H

typedef enum e_nodetype		t_nodetype;
typedef struct s_astree		t_astree;

enum	e_nodetype
{
	NT_PIPE,
	NT_SEMI,
	NT_CMD,
	NT_AND,
	NT_OR_IF,
	NT_AND_IF,
};

struct	s_astree
{
	t_nodetype	type;
	t_tkn		**arg;
	t_astree	*left;
	t_astree	*right;
};

void		ast_debug(t_astree *astree);
t_astree	*ast_build(t_tkn *tkn);

#endif
