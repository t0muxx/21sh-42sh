/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 21:20:02 by cormarti          #+#    #+#             */
/*   Updated: 2018/06/23 20:01:46 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/astree.h"
#include "../../includes/exec.h"
#include "error.h"
#include "utils.h"

int		tkn_arr_len(t_tkn **tkn)
{
	int		len;
	t_tkn	*tmp;

	tmp = *tkn;
	len = 0;
	while (tmp && tmp->type != CHR_NEWLINE)
	{
		if (is_redir(tmp->type))
			tmp = tmp->next;
		else if (tmp->type != CHR_IO_NUMBER
				&& tmp->type != CHR_DQUOTE
				&& tmp->type != CHR_QUOTE)
			len++;
		tmp = tmp->next;
	}
	return (len);
}

char	**lst_arr(t_tkn **tkn, char **env)
{
	char	**args;
	int		len;
	t_tkn	*tmp;

	tmp = *tkn;
	args = NULL;
	len = tkn_arr_len(tkn);
	if (!(args = (char**)malloc(sizeof(char*) * (len + 1))))
		return (NULL);
	args[len] = NULL;
	len = 0;
	if ((args[len] = path_find_in_path(tmp->data, env)) == NULL)
	{
		args[len++] = ft_strdup(tmp->data);
		args[len] = 0;
		return (args);
	}
	len++;
	tmp = tmp->next;
	while (tmp && tmp->data && tmp->type != CHR_NEWLINE)
	{
		if (is_redir(tmp->type))
			tmp = tmp->next;
		else if (tmp->type != CHR_IO_NUMBER
			&& tmp->type != CHR_DQUOTE
			&& tmp->type != CHR_QUOTE)
		{
			args[len] = ft_strdup(tmp->data);
			len++;
		}
		if (!tmp)
			break ;
		tmp = tmp->next;
	}
	return (args);
}

int		exec_cmd(t_astree *astree, char **env)
{
	char	**args;
	char	*cmd_path;
	//	char	*tmp;
	int		i;

	i = 0;
	ft_putendl("in exec cmd");
	ft_putendl(astree->arg[0]->data);
	ft_putnbr(astree->arg[0]->type);
	if (ft_strcmp(astree->arg[0]->data, "") == 0)
		ft_putendl("newline match");
	ft_putendl("in exec cmd");
	args = lst_arr(astree->arg, env);
	ft_putendl(args[0]);
	redirect_cmd(astree->arg);
	execve(args[0], args, env);
	error_print(CMDNOTFOUND, args[0], "");
	exit(EXIT_FAILURE);
	return (1);
}
