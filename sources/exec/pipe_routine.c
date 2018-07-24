/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 08:54:21 by tmaraval          #+#    #+#             */
/*   Updated: 2018/07/24 18:53:19 by tomux            ###   ########.fr       */
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
		new->cmd = lst_arr(astree->arg);
	}
	new->next = NULL;
	return (new);
}

void	pipeline_print(t_pipeline *head)
{
	while (head)
	{
		ft_printf("|%s|\n", head->cmd[0]);
		head = head->next;
	}
}

