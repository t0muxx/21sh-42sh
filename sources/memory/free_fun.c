/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tkn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 02:08:46 by cormarti          #+#    #+#             */
/*   Updated: 2018/09/04 09:54:48 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "astree.h"
#include "exec.h"

void	free_tkn_lst(t_tkn *tkn)
{
	t_tkn	*tmp;

	while (tkn)
	{
		tmp = tkn;
		tkn = tkn->next;
		free(tmp->data);
		free(tmp);
	}
	tkn = NULL;
}

void	free_astree(t_astree *astree)
{
/*	t_tkn	*tmp;

	if (astree->left)
		free_astree(astree->left);
	if (astree->right)
		free_astree(astree->right);
	while (astree->arg)
	{
		ft_putendl("yoyoyo");
		tmp = astree->arg;
		astree->arg = astree->arg->next;
		ft_putendl("yoyoyo");
		if (tmp->data)
			free(tmp->data);
		ft_putendl("yoyoyo");
	}*/
	free(astree);
	astree = NULL;
}

void	free_env(char **env)
{
	int		i;

	i = 0;
	while (env[i])
		free(env[i++]);
	free(env);
}
