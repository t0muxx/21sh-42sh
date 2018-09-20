/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aggregators.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 19:05:20 by cormarti          #+#    #+#             */
/*   Updated: 2018/09/17 15:35:54 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "astree.h"
#include "exec.h"

void		lessand_redir(t_tkn *tkn)
{
	int		fd;
	int		word;

	word = 0;
	fd = STDIN_FILENO;
	if (strdigit(tkn->next->data))
	{
		word = ft_atoi(tkn->next->data);
		if (tkn->prev->type == CHR_IO_NUMBER)
			fd = ft_atoi(tkn->prev->data);
		if (dup2(word, fd) == -1)
		{
			ft_putstr("-bash: ");
			ft_putnbr(fd);
			ft_putendl(": Bad file descriptor");
		}
	}
	else if (tkn->next->type == CHR_DASH)
	{
		if (tkn->prev->type == CHR_IO_NUMBER)
			fd = ft_atoi(tkn->prev->data);
		close(fd);
	}
	else
		ft_putendl("ERROR");
}

void		greatand_redir(t_tkn *tkn)
{
	int		fd;
	int		word;

	word = 0;
	fd = STDOUT_FILENO;
	if (strdigit(tkn->next->data))
	{
		word = ft_atoi(tkn->next->data);
		if (tkn->prev->type == CHR_IO_NUMBER)
			fd = ft_atoi(tkn->prev->data);
		if (dup2(word, fd) == -1)
		{
			ft_putstr_fd("-bash: ", 2);
			ft_putnbr_fd(fd, 2);
			ft_putstr_fd(": Bad file descriptor\n", 2);
		}
	}
	else if (tkn->next->data && tkn->next->data[0] == '-') 
	{
		if (tkn->prev->type == CHR_IO_NUMBER)
			fd = ft_atoi(tkn->prev->data);
		close(fd);
	}
	else
		and_redir(tkn);
}
