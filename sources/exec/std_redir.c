/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 17:48:44 by cormarti          #+#    #+#             */
/*   Updated: 2018/09/06 18:51:36 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "astree.h"
#include "exec.h"
#include <fcntl.h>

static void		and_dgreat_redir(t_tkn *tkn)
{
	int		fd;

	if (access(tkn->next->data, R_OK) == -1
		&& access(tkn->next->data, F_OK) == 0)
	{
		ft_putstr_fd(tkn->next->data, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		exit(EXIT_FAILURE);
	}
	if ((fd = open(tkn->next->data, O_WRONLY | O_CREAT | O_APPEND,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)) == -1)
	{
		ft_putstr_fd(tkn->next->data, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		close(fd);
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) == -1 || dup2(fd, STDERR_FILENO) == -1)
	{
		ft_putstr_fd("fail to redirect output\n", 2);
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
}

static void		and_great_redir(t_tkn *tkn)
{
	int		fd;

	if (access(tkn->next->data, R_OK) == -1
		&& access(tkn->next->data, F_OK) == 0)
	{
		ft_putstr_fd(tkn->next->data, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		exit(EXIT_FAILURE);
	}
	if ((fd = open(tkn->next->data, O_WRONLY | O_CREAT | O_TRUNC,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)) == -1)
	{
		ft_putstr_fd(tkn->next->data, 2);
		ft_putstr_fd(" cannot be opened\n", 2);
		close(fd);
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) == -1 || dup2(fd, STDERR_FILENO) == -1)
	{
		ft_putstr_fd("fail to redirect output\n", 2);
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void			and_redir(t_tkn *tkn)
{
	if (tkn->type == CHR_ANDDGREAT)
		and_dgreat_redir(tkn);
	else
		and_great_redir(tkn);
}
