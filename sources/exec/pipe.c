/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 03:20:55 by cormarti          #+#    #+#             */
/*   Updated: 2018/06/13 13:39:20 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/astree.h"
#include "../../includes/exec.h"

int		node_pipe(t_astree *astree, char **env, int last_exec)
{
	/*static int		fd[2];

	(void)last_exec;
	pipe(fd);
	if (!parent_type)
	{
		dup2(fd[0], 0);
		fork_and_exec(astree->left, env);
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
	}

	return (0);*/
}
