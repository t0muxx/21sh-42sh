/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eol.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 23:03:44 by cormarti          #+#    #+#             */
/*   Updated: 2018/06/01 20:24:52 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

t_tkn	*tkn_newline(char **str)
{
	t_tkn	*tkn;

	tkn = tkn_init(1);
	tkn->data = ft_strncpy(tkn->data, *str, 1);
	tkn->type = CHR_NEWLINE;
	return (tkn);
}
