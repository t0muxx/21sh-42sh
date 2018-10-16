/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dless_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 11:57:49 by cormarti          #+#    #+#             */
/*   Updated: 2018/10/16 15:39:54 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "lexer.h"
#include "astree.h"
#include "exec.h"
#include "get_next_line.h"
#include <fcntl.h>

int		write_input(t_tkn *tkn, char *line, int fd)
{

	ft_putstr_fd("> ", 0);
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
	else
		return (0);
	return (1);
}

void	dless_redir(t_tkn *tkn)
{
	static int	nb;
	char		*line;
	int			fd;
	char		*filename;
	int		tmp_stdio;

	if (!nb || nb == 2147483647)
		nb = 0;
	else
		nb++;
	tmp_stdio = dup(STDIN_FILENO);
	close(STDIN_FILENO);
	dup2(g_stdio, STDIN_FILENO);
	close(g_stdio);
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
	g_stdio = dup(STDIN_FILENO);
	close(fd);
	free(filename);
	free(line);
}
