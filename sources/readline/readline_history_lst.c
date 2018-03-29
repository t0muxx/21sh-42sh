/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_history_lst.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 10:20:06 by tmaraval          #+#    #+#             */
/*   Updated: 2018/02/22 08:05:56 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

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
	new->oldest = NULL;
	new->newest = NULL;
	return (new);
}
