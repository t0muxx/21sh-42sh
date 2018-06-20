/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 21:20:02 by cormarti          #+#    #+#             */
/*   Updated: 2018/06/20 14:07:41 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/astree.h"
#include "../../includes/exec.h"

int		tkn_arr_len(t_tkn **tkn)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (tkn[i] && ft_strcmp(tkn[i]->data, "\n") != 0)
	{
		if (is_redir(tkn[i]->type))
			i++;
		else if (ft_strcmp(tkn[i]->data, "\n") != 0
			&& tkn[i]->type != CHR_IO_NUMBER
			&& tkn[i]->type != CHR_DQUOTE
			&& tkn[i]->type != CHR_QUOTE)
			len++;
		i++;
	}
	return (len);
}

char	**lst_arr(t_tkn **tkn)
{
	char	**args;
	int		len;
	int		i;

	args = NULL;
	i = 0;
	len = tkn_arr_len(tkn);
	if (!(args = (char**)malloc(sizeof(char*) * (len + 1))))
		return (NULL);
	args[len] = NULL;
	len = 0;
	while (tkn[i] && tkn[i]->data && ft_strcmp(tkn[i]->data, "\n") != 0)
	{
		if (is_redir(tkn[i]->type))
			i++;
		else if (tkn[i]->type != CHR_IO_NUMBER
				&& tkn[i]->type != CHR_DQUOTE
				&& tkn[i]->type != CHR_QUOTE)
		{
			args[len] = strdup(tkn[i]->data);
			len++;
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
	ft_putendl("copy tkn data to str array");
	args = lst_arr(astree->arg);
	tmp = args[0];
	args[0] = path_find_in_path(args[0], env);
	free(tmp);
	ft_putstr("execute cmd: ");
	ft_putendl(args[0]);
	redirect_cmd(astree->arg);
	execve(args[0], args, env);
	return (0);
}
