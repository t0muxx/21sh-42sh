/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 17:08:16 by tmaraval          #+#    #+#             */
/*   Updated: 2018/03/30 09:08:19 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CURSOR_H
# define CURSOR_H

# include "readline.h"

void	cursor_delete_line(int linebr);
void	cursor_move_left_upd_tbuffer(int count, t_buffer *tbuffer);
void	cursor_move_right_upd_tbuffer(int count, t_buffer *tbuffer);
void	cursor_up_line(int linenbr);
void	cursor_move_left_next_word(t_buffer *tbuffer);
void	cursor_move_right_next_word(t_buffer *tbuffer);
void	cursor_reset_line(t_buffer *tbuffer);
#endif
