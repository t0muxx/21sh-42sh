/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 21:20:02 by cormarti          #+#    #+#             */
/*   Updated: 2018/06/02 05:10:32 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/astree.h"
#include "../../includes/exec.h"

int		tkn_arr_len(t_tkn **tkn)
{
	int		i;

	i = 0;
	while (tkn[i])
		i++;
	return (i);
}

char	**lst_arr(t_tkn **tkn)
{
	char	**args;
	int		i;

	args = NULL;
	i = tkn_arr_len(tkn);;
	if (!(args = (char**)malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	args[i] = NULL;
	i = 0;
	while (tkn[i] && tkn[i]->data)
	{
		args[i] = strdup(tkn[i]->data);
		i++;
	}
	return (args);
}

int		exec_cmd(t_astree *astree, char **env)
{
	char	**args;

	if (is_redirected(astree->arg))
	{
		ft_putendl("is redirected, exit now");
		return (0);	
		//	redirect_cmd(astree->arg);
	}
	ft_putendl("copy tkn data to str array");
	args = lst_arr(astree->arg);
	ft_putstr("execute cmd: ");
	ft_putendl(args[0]);	
	execve(args[0], args, env);
	return (1);
}
