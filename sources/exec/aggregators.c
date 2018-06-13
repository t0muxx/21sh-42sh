/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aggregators.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 19:05:20 by cormarti          #+#    #+#             */
/*   Updated: 2018/06/13 19:40:54 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/astree.h"
#include "../../includes/exec.h"

static void	less_and_redir(t_tkn *tkn)
{
	int		fd;
	int		from;

	if (strdigit(tkn->next->data))
	{
		fd = ft_atoi(tkn->next->data);
		if (tkn->prev->type == CHR_IO_NUMBER)
			from = ft_atoi(tkn->prev->data);
		else
			from = STDIN_FILENO;
		if (dup2(fd, from) == -1)
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
		else
			fd = STDIN_FILENO;
		close (fd);
	}
	else
		ft_putendl("ERROR");
	close(fd);
}
	
static void	great_and_redir(t_tkn *tkn)
{
	int		fd;
	int		from;

	if (strdigit(tkn->next->data))
	{
		fd = ft_atoi(tkn->next->data);
		if (tkn->prev->type == CHR_IO_NUMBER)
			from = ft_atoi(tkn->prev->data);
		else
			from = STDOUT_FILENO;
		if (dup2(fd, from) == -1)
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
		else
			fd = STDOUT_FILENO;
		close (fd);
	}
	else
		ft_putendl("ERROR");
	close(fd);
}
