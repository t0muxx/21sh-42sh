/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_history.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 09:15:03 by tmaraval          #+#    #+#             */
/*   Updated: 2018/09/17 11:02:39 by tmaraval         ###   ########.fr       */
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

void			history_print_reset(t_buffer *tbuffer)
{
	char			*cmd;

	line_go_begin(tbuffer);
	tbuffer->cnt = 0;
	tbuffer->index = 0;
	tputs(tbuffer->termcap->cd, 0, ft_putcc);
	prompt_print(tbuffer);
	ft_bzero(tbuffer->buffer, BUFFER_SIZE);
	cmd = ft_strdup("");
	ft_memcpy(tbuffer->buffer, cmd, ft_strlen(cmd));
	insert_tbuffer(tbuffer);
	free(cmd);
}

void			history_print(t_buffer *tbuffer, t_cmd_hist **toprint)
{
	char			*cmd;

	line_go_begin(tbuffer);
	tbuffer->cnt = 0;
	tbuffer->index = 0;
	tputs(tbuffer->termcap->cd, 0, ft_putcc);
	prompt_print(tbuffer);
	if (toprint && (*toprint) != NULL)
	{
		ft_bzero(tbuffer->buffer, BUFFER_SIZE);
		cmd = ft_strdup((*toprint)->cmd);
		ft_memcpy(tbuffer->buffer, cmd, ft_strlen(cmd));
		insert_tbuffer(tbuffer);
		free(cmd);
	}
}

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

int				histfile_get_linenbr(char *base_path)
{
	int fd;
	int nbr;
	char *line;

	nbr = 0;
	if (access(base_path, F_OK) != 1)
	{
		if ((fd = open(base_path, O_WRONLY | O_CREAT, 0644)) == -1)
		{
			ft_putstr_fd("Can't create .history check perm\n", 2);
			close(fd);
			return (0);
		}
		close(fd);
	}
	if ((fd = open(base_path, O_RDONLY, 0644)) == -1)
	{
		ft_putstr_fd("Can't open .history\n", 2);
		close(fd);
		return (0);
	}
	while (get_next_line(fd, &line) > 0)
	{
		free(line);
		nbr++;
	}
	return (nbr);	
}

void			history_add(char *base_path, t_buffer *tbuffer)
{
	int	fd;
	int i;

	i = 0;
	if ((fd = open(base_path, O_WRONLY | O_APPEND, 0644)) == -1)
		ft_putstr_fd("Can't open .history\n", 2);
	while (tbuffer->head_hist->enddown != -1)
		tbuffer->head_hist = tbuffer->head_hist->oldest;
	while (i <= histfile_get_linenbr(tbuffer->base_path))
	{
		tbuffer->head_hist = tbuffer->head_hist->newest;
		i++;
	}
	while (tbuffer->head_hist->enddown != 1)
	{
		if (ft_strlen(tbuffer->head_hist->cmd) != 0)
		{
			write(fd, tbuffer->head_hist->cmd, ft_strlen(tbuffer->head_hist->cmd));
			write(fd, "\n", 1);
		}
		tbuffer->head_hist = tbuffer->head_hist->newest;
	}
	close(fd);
}
