/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bang.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 01:15:36 by cormarti          #+#    #+#             */
/*   Updated: 2018/05/15 17:19:55 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

t_tkn	*tkn_bang(char **str)
{
	t_tkn	*tkn;
	char	*line;

	line = *str;
	tkn = tkn_init(1);
	tkn->data[0] = '!';
	tkn->type = CHR_BANG;
	line++;
	*str = line;
	return (tkn);
}
