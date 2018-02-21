/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_history.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 09:15:03 by tmaraval          #+#    #+#             */
/*   Updated: 2018/02/21 11:15:44 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

/* readline_history_add add command at the end 	*/
/* of the file .history 						*/ 

t_cmd_hist		*readline_history_read(void)
{
	int 		fd;
	char		*line;
	t_cmd_hist	*head;
	t_cmd_hist	*new;

	head = NULL;
	if ((fd = open(HISTORY_FILE, O_RDONLY)) == -1)
	{
		ft_printf("ERROR UNKNW\n");
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

	if (access(HISTORY_FILE, F_OK) != 1)
	{
		if ((fd = open(HISTORY_FILE, O_WRONLY | O_CREAT)) == -1)
			ft_printf("ERROR UNKNOW\n");
		close(fd);
		if ((fd = open(HISTORY_FILE, O_WRONLY | O_APPEND)) == -1)
			ft_printf("ERROR UNKNOW\n");
	}
	else
	{
		if ((fd = open(HISTORY_FILE, O_WRONLY | O_APPEND)) == -1)
			ft_printf("ERROR UNKNOW\n");
	}
	write(fd, cmd, ft_strlen(cmd));
	write(fd, "\n", 1);
	close(fd);
}
