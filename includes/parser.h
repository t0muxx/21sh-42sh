/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 06:03:34 by cormarti          #+#    #+#             */
/*   Updated: 2018/10/03 19:59:32 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "lexer.h"

int		parse(t_tkn *tkn);
int		is_complete_cmd(t_tkn *tkn);
int		is_and_or(t_tkn **tkn);
int		is_newline_list(t_tkn **tkn);
int		is_cmd_name(t_tkn **tkn);
int		is_cmd_word(t_tkn **tkn);
int		is_cmd_suffix(t_tkn **tkn);
int		is_cmd_prefix(t_tkn **tkn);
int		is_simple_cmd(t_tkn **tkn);
int		is_command(t_tkn **tkn);
int		is_here_end(t_tkn **tkn);
int		is_io_file(t_tkn **tkn);
int		is_io_here(t_tkn **tkn);
int		is_io_redirect(t_tkn **tkn);
int		is_list(t_tkn **tkn);
int		is_pipe_seq(t_tkn **tkn);
int		is_pipeline(t_tkn **tkn);
int		is_separator_op(t_tkn **tkn);
int		is_separator(t_tkn **tkn);
int		is_filename(t_tkn **tkn);

#endif
