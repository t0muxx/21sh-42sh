/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 21:20:02 by cormarti          #+#    #+#             */
/*   Updated: 2018/09/19 11:58:53 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/astree.h"
#include "../../includes/exec.h"
#include "error.h"
#include "utils.h"

int		tkn_arr_len(t_tkn *tkn)
{
	int		len;
	t_tkn	*tmp;

	tmp = tkn;
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

char	**lst_arr(t_tkn *tkn)
{
	char	**args;
	int		len;
	t_tkn	*tmp;

	tmp = tkn;
	args = NULL;
	len = tkn_arr_len(tkn);
	if (!(args = (char**)malloc(sizeof(char*) * (len + 1))))
		error_malloc_err(0);
	args[len] = NULL;
	len = 0;
	while (tmp && tmp->data && tmp->type != CHR_NEWLINE)
	{
		if (is_redir(tmp->type))
			tmp = tmp->next;
		else if (tmp->type != CHR_IO_NUMBER
			&& tmp->type != CHR_DQUOTE
			&& tmp->type != CHR_QUOTE)
			args[len++] = ft_strdup(tmp->data);
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

	if (astree)
	{
		args = lst_arr(astree->arg);
		redirect_cmd(astree->arg);
		if (args == NULL || args[0] == NULL)
			exit(EXIT_SUCCESS);
		cmd_path = path_find_in_path(args[0], env);
		execve(cmd_path, args, env);
		error_print(CMDNOTFOUND, args[0], "");
	}
	exit(EXIT_FAILURE);
	return (1);
}
