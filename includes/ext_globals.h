/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ext_globals.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 10:12:20 by tmaraval          #+#    #+#             */
/*   Updated: 2018/10/16 15:16:34 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXT_GLOBALS_H
# define EXT_GLOBALS_H

# include "global.h"

t_global	g_globals[128] =
{
	{NULL, NULL},
};

int			g_stdio = 0;
int			g_quote_state = 0;

#endif
