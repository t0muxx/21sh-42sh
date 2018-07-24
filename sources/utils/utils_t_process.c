/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_t_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 12:17:04 by tmaraval          #+#    #+#             */
/*   Updated: 2018/07/24 17:31:06 by tomux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void			t_process_free(t_process *list)
{
	t_process *temp;

	while (list)
	{
		temp = list;
		list = list->next;
		free(temp);
		temp = NULL;
	}
	list = NULL;
}

t_process		*t_process_new(pid_t pid)
{
	t_process *new;

	if (!(new = malloc(sizeof(t_process))))
		return (NULL);
	else
		new->pid = pid;
	new->next = NULL;
	return (new);
}

void		t_process_add(t_process **last, t_process *new)
{
	t_process *list;

	list = *last;
	if (*last == NULL)
	{
		*last = new;
		return ;
	}
	while (list->next != NULL)
	{
		list = list->next;
	}
	list->next = new;
}
