/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ext_node_type.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 02:57:05 by cormarti          #+#    #+#             */
/*   Updated: 2018/06/03 20:19:20 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXT_NODE_TYPE_H
# define EXT_NODE_TYPE_H

#include "exec.h"

t_node_type		node_fun[] =
{
	//{NT_PIPE, &node_pipe},
	//{NT_PIPE, &node_and},
	{NT_AND_IF, &node_and_if},
	{NT_OR_IF, &node_or_if},
	//{NT_PIPE, &node_semi},
};

#endif
