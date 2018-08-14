/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 08:54:21 by tmaraval          #+#    #+#             */
/*   Updated: 2018/08/14 10:04:44 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/types.h>
#include <sys/wait.h>
#include "exec.h"
#include "astree.h"
#include "lexer.h"

void		pipeline_add(t_pipeline **last, t_pipeline *new)
{
	t_pipeline *list;

	list = *last;
	if (*last == NULL)
	{
		*last = new;
		return ;
	}
	while (list->next != NULL)
		list = list->next;
	list->next = new;
}

t_pipeline	*pipeline_new(t_astree *astree)
{
	t_pipeline *new;

	if (!(new = (t_pipeline *)malloc(sizeof(t_pipeline))))
		return (NULL);
	else
	{
		if (!(new->node = malloc(sizeof(t_astree))))
			return (NULL);
		new->node->type = astree->type;
		if (!(new->node->arg = malloc(sizeof(t_tkn))))
			return (NULL);
		ft_memcpy(new->node->arg, astree->arg, sizeof(t_tkn));
		new->node->left = NULL;
		new->node->right = NULL;
		new->cmd = lst_arr(astree->arg);
	}
	new->next = NULL;
	return (new);
}

void		pipeline_free(t_pipeline *head)
{
	t_pipeline *tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->cmd);
		free(tmp->node->arg);
		free(tmp->node);
		free(tmp);
		tmp = NULL;
	}
	head = NULL;
}

void		pipeline_print(t_pipeline *pipeline)
{
	while (pipeline)
	{
		ft_printf("|%s|->", pipeline->cmd[0]);
		pipeline = pipeline->next;
	}
	ft_printf("\n");
}
