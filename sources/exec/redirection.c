/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 00:42:28 by cormarti          #+#    #+#             */
/*   Updated: 2018/06/02 00:49:24 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/astree.h"
#include "../../includes/exec.h"

int		is_redirected(t_tkn **tkn)
{
	int		i;

	i = 0;
	while (tkn[i])
	{
		if (tkn[i]->type == CHR_LESS
			|| tkn[i]->type == CHR_DLESS
			|| tkn[i]->type == CHR_GREAT
			|| tkn[i]->type == CHR_DGREAT)
			return (1);
		i++;
	}
	return (0);
}
