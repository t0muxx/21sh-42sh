/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_history_lst.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 10:20:06 by tmaraval          #+#    #+#             */
/*   Updated: 2018/09/17 11:40:33 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void		history_lst_free(t_cmd_hist *head)
{
	t_cmd_hist *tmp;
	
	while (head->enddown != -1)
		head = head->oldest;
	while (head)
	{
		tmp = head;
		head = head->newest;
		free(tmp->cmd);
		free(tmp);
		tmp = NULL;
	}
	head = NULL;
}

t_cmd_hist 	*history_lst_get_lastnode(t_cmd_hist **head)
{
	t_cmd_hist *tmphead;

	tmphead = *head;
	while (tmphead && tmphead->enddown != -1)
		tmphead = tmphead->oldest;
	while (tmphead && tmphead->newest->enddown != 1)
		tmphead = tmphead->newest;
	return (tmphead);	
}

void		history_lst_addcmd_to_lst(t_cmd_hist **head, t_cmd_hist *lastnode, t_cmd_hist *new)
{
	if (head)
		NULL;
	lastnode->newest->oldest = new;
	new->newest = lastnode->newest;
	new->oldest = lastnode;
	lastnode->newest = new;
}

void		history_lst_addcmd(t_cmd_hist **head, char *cmd)
{
	t_cmd_hist *new;
	t_cmd_hist *cpy;

	new = history_lst_new(cmd);
	history_lst_addcmd_to_lst(head,
	history_lst_get_lastnode(head), new);
	cpy = *head;
}

void		history_lst_add(t_cmd_hist **head, t_cmd_hist *new)
{
	new->oldest = *head;
	new->newest = NULL;
	if (*head != NULL)
		(*head)->newest = new;
	*head = new;
}

t_cmd_hist	*history_lst_new(char *cmd)
{
	t_cmd_hist *new;

	if (!(new = malloc(sizeof(t_cmd_hist))))
		error_malloc_err();
	if (cmd == NULL)
		new->cmd = NULL;
	else
	{
		if (!(new->cmd = malloc(sizeof(char) * (ft_strlen(cmd) + 1))))
			error_malloc_err();
		ft_bzero(new->cmd, ft_strlen(cmd) + 1);
		ft_memcpy(new->cmd, cmd, ft_strlen(cmd));
	}
	new->enddown = 0;
	new->oldest = NULL;
	new->newest = NULL;
	return (new);
}
