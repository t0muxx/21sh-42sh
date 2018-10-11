/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ext_node_fun.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 11:25:03 by tmaraval          #+#    #+#             */
/*   Updated: 2018/10/11 11:25:12 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXT_NODE_FUN_H
# define EXT_NODE_FUN_H

# include "exec.h"

t_node_type		g_node_fun[] =
{
	{NT_SEMI, &node_semi},
	{NT_AND_IF, &node_and_if},
	{NT_OR_IF, &node_or_if},
	{NT_PIPE, &node_pipe},
};

#endif
