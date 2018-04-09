/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eol.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 23:03:44 by cormarti          #+#    #+#             */
/*   Updated: 2018/03/31 01:19:06 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

t_tkn	*tkn_eol(char **str)
{
	t_tkn	*tkn;

	tkn = tkn_init(1);
	tkn->data = ft_strncpy(tkn->data, *str, 1);
	tkn->type = CHR_EOL;
	return (tkn);
}
