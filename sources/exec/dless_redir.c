/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dless_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 11:57:49 by cormarti          #+#    #+#             */
/*   Updated: 2018/06/13 18:09:28 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/astree.h"
#include "../../includes/exec.h"
#include "../../includes/get_next_line.h"
#include <fcntl.h>

void	dless_redir(t_tkn *tkn)
{
	static int	nb;
	char	*line;
	int		fd;
	char	*filename;

	if (!nb)
		nb = 0;
	else
		nb++;
	line = NULL;
	filename = ft_strjoin("/tmp/heredoc", ft_itoa(nb));
//	term_close();
	if ((fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)) == -1)
		ft_putendl("fail to open here");
	while (1)
	{
		ft_putstr("> ");
		if (get_next_line(0, &line) == 1 && line && line[0] != '\0')
		{
			if (ft_strcmp(line, tkn->data) == 0)
				break ;
			else
			{
				write(fd, line, ft_strlen(line));
				write(fd, "\n", 1);
				free(line);
			}
		}
	}
	close(fd);
	fd = open(filename, O_RDONLY,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if (dup2(fd, STDIN_FILENO) == -1)
		ft_putendl("fail dup2");
	close(fd);
	free(filename);
	free(line);
}
