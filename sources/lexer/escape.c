/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 02:12:01 by cormarti          #+#    #+#             */
/*   Updated: 2018/09/05 12:48:38 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

t_tkn	*tkn_escape(char **str)
{
	char	*line;

	line = *str;
	if (*(line + 1) == '\0')
	{
		*str += 1;
		return (NULL);
	}
	return (tkn_word(str));
}
