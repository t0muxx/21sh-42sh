/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 00:42:28 by cormarti          #+#    #+#             */
/*   Updated: 2018/06/20 12:02:30 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/astree.h"
#include "../../includes/exec.h"
#include <fcntl.h>

int		is_redir(t_tkn_type type)
{
	if (type == CHR_GREAT
		|| type == CHR_DGREAT
		|| type == CHR_LESS
		|| type == CHR_DLESS
		|| type == CHR_LESSAND
		|| type == CHR_GREATAND)
		return (1);
	return (0);
}

static void	great_redir(t_tkn *tkn)
{
	int		fd;
	int		from;

	if ((fd = open(tkn->next->data, O_WRONLY | O_CREAT | O_TRUNC, 
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)) == -1)
	{
		ft_putstr("fail to open ");
		ft_putendl(tkn->next->data);
	}
	from = (tkn->prev->type == CHR_IO_NUMBER) ? 
		ft_atoi(tkn->prev->data) : STDOUT_FILENO;
	if (dup2(fd, from) == -1)
		ft_putendl("fail to dup2");
	close(fd);
}

static void	less_redir(t_tkn *tkn)
{
	int		fd;
		
	if ((fd = open(tkn->data, O_RDONLY, 
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)) == -1)
	{
		ft_putstr("fail to open ");
		ft_putendl(tkn->data);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
		ft_putendl("fail dup2");
	close(fd);
}

static void	dgreat_redir(t_tkn *tkn)
{
	int		fd;
		
	if ((fd = open(tkn->data, O_WRONLY | O_CREAT | O_APPEND, 
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)) == -1)
	{
		ft_putstr("fail to open ");
		ft_putendl(tkn->data);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
		ft_putendl("fail dup2");
	close(fd);
}

void	redirect_cmd(t_tkn **tkn)
{
	int		i;

	i = 0;
	while (tkn[i] != NULL)
	{
		if (tkn[i]->type == CHR_LESS)
			less_redir(tkn[i++]);
		else if (tkn[i]->type == CHR_GREAT)
			great_redir(tkn[i++]);
		else if (tkn[i]->type == CHR_GREATAND)
			greatand_redir(tkn[i++]);
		else if (tkn[i]->type == CHR_DGREAT)
			dgreat_redir(tkn[i++]);
		else if (tkn[i]->type == CHR_DLESS)
			dless_redir(tkn[i++]);
		else if (tkn[i]->type == CHR_LESSAND)
			lessand_redir(tkn[i++]);
		if (!tkn[i])
			break ;
		i++;
	}
}
