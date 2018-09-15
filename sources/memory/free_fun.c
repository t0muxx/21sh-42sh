/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tkn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 02:08:46 by cormarti          #+#    #+#             */
/*   Updated: 2018/09/15 18:02:16 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "astree.h"
#include "exec.h"

void	free_astree(t_astree *astree)
{
	t_tkn	*tmp;

	tmp = NULL;
	if (astree->left)
		free_astree(astree->left);
	if (astree->right)
		free_astree(astree->right);
	while (astree->arg)
	{
		tmp = astree->arg;
		astree->arg = astree->arg->next;
		if (tmp->data)
			free(tmp->data);
		tmp->next = NULL;
		tmp->prev = NULL;
		free(tmp);
		tmp = NULL;
	}
	astree->left = NULL;
	astree->right = NULL;
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
