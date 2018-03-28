/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_history.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 09:15:03 by tmaraval          #+#    #+#             */
/*   Updated: 2018/03/28 08:10:03 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "cursor.h"
#include <term.h>

/*
** readline_history_print print the last command based on .history
** it update cnt and buffer in order to get execute it if the user
** press enter
*/

void			readline_history_print(t_cmd_hist **head, t_cmd_hist *next,
t_buffer *tbuffer)
{
	cursor_move_left_upd_tbuffer(BUFFER_SIZE, tbuffer);
	tputs(tbuffer->termcap->cd, 0, ft_putcc);
	readline_print_prompt(TRUE);
	tbuffer->cnt = 0;
	tbuffer->index = 0;
	if (*head != NULL)
	{
		ft_bzero(tbuffer->buffer, BUFFER_SIZE);
		ft_memcpy(tbuffer->buffer, (*head)->cmd, ft_strlen((*head)->cmd));
		readline_print_upd_tbuffer(tbuffer);
	}
	if (next != NULL)
		*head = next;
}

/*
** readline_history_read_line just gnl
** on the .history file and return
** the linkedt list with history
*/

t_cmd_hist		*readline_history_read_line(int fd)
{
	t_cmd_hist	*head;
	t_cmd_hist	*new;
	char		*line;

	head = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		new = history_lst_new(line);
		history_lst_add(&head, new);
		free(line);
	}
	return (head);
}

/*
** readline_history_add add command at the end
** of the file .history
*/

t_cmd_hist		*readline_history_read(void)
{
	int			fd;
	t_cmd_hist	*head;

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
	head = readline_history_read_line(fd);
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
