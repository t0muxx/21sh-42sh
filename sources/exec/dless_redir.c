/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dless_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 11:57:49 by cormarti          #+#    #+#             */
/*   Updated: 2018/09/06 15:03:01 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "astree.h"
#include "exec.h"
#include "get_next_line.h"
#include <fcntl.h>

int		write_input(t_tkn *tkn, char *line, int fd)
{
	ft_putstr_fd("> ", 2);
	if (get_next_line(0, &line) == 1 && line)
	{
		if (ft_strcmp(line, tkn->next->data) == 0)
			return (0);
		else
		{
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
			free(line);
		}
	}
	return (1);
}

void	dless_redir(t_tkn *tkn)
{
	static int	nb;
	char		*line;
	int			fd;
	char		*filename;

	nb = (!nb) ? 1 : nb++;
	line = NULL;
	filename = ft_strjoin("/tmp/heredoc", ft_itoa(nb));
	if ((fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)) == -1)
		ft_putendl("fail to open here");
	while (1)
		if (!write_input(tkn, line, fd))
			break ;
	close(fd);
	fd = open(filename, O_RDONLY,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if (!tkn->next->next || tkn->next->next->type != CHR_DLESS)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			ft_putendl("fail dup2");
	}
	close(fd);
	free(filename);
	free(line);
}
