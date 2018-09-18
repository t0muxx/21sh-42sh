/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 04:23:59 by cormarti          #+#    #+#             */
/*   Updated: 2018/09/18 09:16:51 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parser.h"
#include "astree.h"

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
		*head = NULL;
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
