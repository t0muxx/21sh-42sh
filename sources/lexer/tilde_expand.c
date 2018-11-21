/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 08:50:41 by tmaraval          #+#    #+#             */
/*   Updated: 2018/11/21 09:11:01 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "env.h"

int		is_tilde_type(char *str)
{
	int		len;

	len = ft_strlen(str);
	if (len > 0 && str[0] == '~')
	{
		if (len > 1 && str[1] != '/')
			return (0);
		else
			return (1);
	}
	return (0);
}

char	*tilde_expand(char **str, char ***env)
{
	char *path;
	char *new;

	if ((path = env_get_var("HOME", *env)) == NULL)
	{
		ft_putendl_fd("HOME is not defined, can't expand", 2);
		free(path);
		return (*str);
	}
	new = ft_strjoin(path, *str + 1);
	free(path);
	free(*str);
	return (new);
}

void	tilde_exp_browse_tkn(t_tkn *tkn, char ***env)
{
	t_tkn *cpy;

	cpy = tkn;
	while (cpy != NULL)
	{
		if (cpy->type == CHR_TILDE)
		{
			cpy->data = tilde_expand(&cpy->data, env);
			cpy->type = CHR_WORD;
		}
		cpy = cpy->next;
	}
}
