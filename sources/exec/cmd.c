/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 21:20:02 by cormarti          #+#    #+#             */
/*   Updated: 2018/06/18 14:47:47 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/astree.h"
#include "../../includes/exec.h"
#include "error.h"
#include "utils.h"

int		tkn_arr_len(t_tkn **tkn)
{
	int		i;

	i = 0;
	while (tkn[i])
		i++;
	return (i);
}

char	**lst_arr(t_tkn **tkn, char **env)
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
		if (i == 0)
		{
			if ((args[i] = path_find_in_path(tkn[i]->data, env)) == NULL)
			{
				error_print(CMDNOTFOUND, tkn[0]->data, "");
				utils_free_2darray((void **)args);
			   	return (NULL);	
			}
		}
		else
		{
			if (!ft_strcmp(tkn[i]->data, "\n"))
				args[i] = 0;
			else
				args[i] = strdup(tkn[i]->data);
		}
		i++;
	}
	return (args);
}

int		exec_cmd(t_astree *astree, char **env)
{
	char	**args;
	char	*tmp;
	int		i;

	i = 0;
	if (is_redirected(astree->arg))
	{
		ft_putendl("is redirected, exit now");
		return (0);	
		//	redirect_cmd(astree->arg);
	}
	ft_putendl("copy tkn data to str array");
	if ((args = lst_arr(astree->arg, env)) == NULL)
		return (-1);
	ft_putstr("execute cmd: ");
	ft_putendl(args[0]);
	execve(args[0], args, env);
	return (1);
}
