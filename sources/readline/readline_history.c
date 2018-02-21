/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_history.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 09:15:03 by tmaraval          #+#    #+#             */
/*   Updated: 2018/02/21 17:29:11 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void			readline_history_print(t_cmd_hist **head, t_cmd_hist *next)
{
	cursor_move_left(BUFFER_SIZE);
	ft_putstr("\033[2K");
	ft_putstr("$> ");
	if (*head != NULL)
		write(0, (*head)->cmd, ft_strlen((*head)->cmd));
	if (next != NULL)
		*head = next;
}

/* 
** readline_history_add add command at the end
** of the file .history 						
*/ 
t_cmd_hist		*readline_history_read(void)
{
	int 		fd;
	char		*line;
	t_cmd_hist	*head;
	t_cmd_hist	*new;

	head = NULL;
	if (access(HISTORY_FILE, F_OK) != 1)
	{
		if ((fd = open(HISTORY_FILE, O_WRONLY | O_CREAT)) == -1)
		{
			ft_putstr_fd("Can't create .history check perm\n", 2);
			close(fd);
			return (NULL);	
		}
		close(fd);
	}
	if ((fd = open(HISTORY_FILE, O_RDONLY)) == -1)
	{
		ft_putstr_fd("Can't open .history\n", 2);	
		close(fd);
		return (NULL);
	}
	while (get_next_line(fd, &line) > 0)
	{
		new = history_lst_new(line);
		history_lst_add(&head, new);
		free(line);
	}
	close(fd);
	return (head);
}

void			readline_history_add(char *cmd)
{
	int	fd;

	if ((fd = open(HISTORY_FILE, O_WRONLY | O_APPEND)) == -1)
		ft_putstr_fd("Can't open .history\n", 2);	
	write(fd, cmd, ft_strlen(cmd));
	write(fd, "\n", 1);
	close(fd);
}
