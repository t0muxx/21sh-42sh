/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aggregators.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 19:05:20 by cormarti          #+#    #+#             */
/*   Updated: 2018/06/18 16:06:54 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/astree.h"
#include "../../includes/exec.h"

/*void	less_and_redir(t_tkn *tkn)
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
}*/
	
void	greatand_redir(t_tkn *tkn)
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
		if (dup2(fd, word) == -1)
		{
			ft_putstr("-bash: ");
			ft_putnbr(fd);
			ft_putendl(": Bad file descriptor");
		}
		//close(fd);
	}
	else if (tkn->next->type == CHR_DASH)
	{
		if (tkn->prev->type == CHR_IO_NUMBER)
			fd = ft_atoi(tkn->prev->data);
		close (fd);
	}
	else
		ft_putendl("ERROR");
}
