/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_history.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 09:15:03 by tmaraval          #+#    #+#             */
/*   Updated: 2018/09/18 09:44:53 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "cursor.h"
#include <term.h>

/*
** readline_history_read_line just gnl
** on the .history file and return
** the linkedt list with history
*/

void			history_lst_createnull(t_cmd_hist **new,
t_cmd_hist **head, int enddown)
{
	(*new)->newest = NULL;
	(*new)->oldest = NULL;
	(*new)->cmd = NULL;
	(*new)->enddown = enddown;
	history_lst_add(head, *new);
}

t_cmd_hist		*history_read_line(int fd)
{
	t_cmd_hist	*head;
	t_cmd_hist	*new;
	char		*line;

	head = NULL;
	if ((new = malloc(sizeof(t_cmd_hist))) != NULL)
		history_lst_createnull(&new, &head, -1);
	while (get_next_line(fd, &line) > 0)
	{
		new = history_lst_new(line);
		history_lst_add(&head, new);
		free(line);
	}
	if ((new = malloc(sizeof(t_cmd_hist))) != NULL)
		history_lst_createnull(&new, &head, 1);
	return (head);
}

/*
** readline_history_add add command at the end
** of the file .history
*/

t_cmd_hist		*history_read(char *base_path)
{
	int			fd;
	t_cmd_hist	*head;

	head = NULL;
	if (access(base_path, F_OK) != 1)
	{
		if ((fd = open(base_path, O_WRONLY | O_CREAT, 0644)) == -1)
		{
			ft_putstr_fd("Can't create .history check perm\n", 2);
			close(fd);
			return (NULL);
		}
		close(fd);
	}
	if ((fd = open(base_path, O_RDONLY, 0644)) == -1)
	{
		ft_putstr_fd("Can't open .history\n", 2);
		close(fd);
		return (NULL);
	}
	head = history_read_line(fd);
	close(fd);
	return (head);
}

void			history_add(char *base_path, char *cmd)
{
	int	fd;

	if ((fd = open(base_path, O_WRONLY | O_APPEND, 0644)) == -1)
		ft_putstr_fd("Can't open .history\n", 2);
	if (ft_strlen(cmd) != 0)
	{
		write(fd, cmd, ft_strlen(cmd));
		write(fd, "\n", 1);
	}
	close(fd);
}
