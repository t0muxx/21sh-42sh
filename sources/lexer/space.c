/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wspace.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 00:49:49 by cormarti          #+#    #+#             */
/*   Updated: 2018/05/15 18:12:42 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

t_tkn	*tkn_htab(char **str)
{
	char	*line;

	line = *str;
	while (*line == '\t')
		line++;
	*str = line;
	return (NULL);
}

t_tkn	*tkn_wspace(char **str)
{
	char	*line;

	line = *str;
	while (*line == ' ')
		line++;
	*str = line;
	return (NULL);
}
