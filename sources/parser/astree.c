/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 04:23:59 by cormarti          #+#    #+#             */
/*   Updated: 2018/09/15 19:28:04 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "astree.h"

/*void				ast_debug(t_astree *astree)
{
	int		i;

	i = 0;
	if (!astree)
		return ;
	ft_putstr("root node type : ");
	ft_putnbr(astree->type);
	ft_putstr("\n");
	if (astree->type == NT_CMD)
		ft_putendl(astree->arg[0]->data);
	while (astree)
	{
		if (astree->left)
		{
		ft_putstr("left : ");
		ft_putnbr(astree->left->type);
		ft_putstr("\n");
		ft_putstr("first data = ");
		if (astree->left->type == NT_CMD)
		{
			i = 0;
			while (astree->left->arg[i])
			{
				ft_putstr(astree->left->arg[i]->data);
				ft_putstr(" ");
				i++;
			}
			ft_putstr("\n");
		}
		else
			ft_putendl("NULL");
		}
		if (astree->right)
		{
			ft_putstr("right : ");
			ft_putnbr(astree->right->type);
			ft_putstr("\n");
			ft_putstr("first data = ");
			if (astree->right->type == NT_CMD)
			{
				i = 0;
				while (astree->right->arg[i])
				{
					ft_putstr(astree->right->arg[i]->data);
					ft_putstr(" ");
					i++;
				}
				ft_putstr("\n");
			}
			else
				ft_putendl("NULL");
		}
		astree = astree->left;
	}
}*/

static void			lst_cut_tkn(t_tkn **head)
{
	t_tkn	*tmp;

	tmp = *head;
	if (!head || !(*head))
		return ;
	if (tmp->prev)
	{
		*head = (*head)->prev;
		free(tmp->data);
		free(tmp);
		tmp = NULL;
		(*head)->next = NULL;
	}	
	else
	{
		*head = NULL;
	}
}

static t_nodetype	node_type(t_tkn_type tkn_type)
{
	t_nodetype	type;

	if (tkn_type == CHR_PIPE)
		type = NT_PIPE;
	else if (tkn_type == CHR_SEMI)
		type = NT_SEMI;
	else if (tkn_type == CHR_AND)
		type = NT_AND;
	else if (tkn_type == CHR_OR_IF)
		type = NT_OR_IF;
	else if (tkn_type == CHR_AND_IF)
		type = NT_AND_IF;
	else
		type = NT_CMD;
	return (type);
}

static t_tkn		*dup_arg(t_tkn *token, int arg_len)
{
	t_tkn	*arg;

	if (!token)
		return (NULL);
	if (arg_len)
		NULL ;
	arg = token;
	arg->prev = NULL;
	while (token && node_type(token->type) == NT_CMD)
	{
		if (arg->next)
			arg = arg->next;
		token = token->next;
	}
	arg->next = NULL;
	while (arg->prev)
		arg = arg->prev;
	return (arg);
}

static t_astree		*ast_new_node(t_tkn *token, int arg_len)
{
	t_astree	*node;

	if ((node = (t_astree*)malloc(sizeof(t_astree))) == NULL)
		return (NULL);
	node->type = node_type(token->type);
	node->arg = (node->type == NT_CMD) ? dup_arg(token, arg_len) : NULL;
	node->is_root_node = 0;
	node->parent = 0;
	node->root_pipe = 0;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_astree			*ast_build(t_tkn *tkn)
{
	t_astree	*node;
	int			arg_len;

	arg_len = 0;
	node = NULL;
	while (tkn)
	{
		if (node_type(tkn->type) != NT_CMD || !tkn->prev)
		{
			node = ast_new_node(tkn, arg_len);
			if (tkn->prev && tkn->next)
				node->right = ast_new_node(tkn->next, arg_len);
			lst_cut_tkn(&tkn);
			break ;
		}
		tkn = tkn->prev;
		arg_len++;
	}
	if (tkn)
		node->left = ast_build(tkn);
	return (node);
}
