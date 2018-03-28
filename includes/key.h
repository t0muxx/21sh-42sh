/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 08:44:54 by tmaraval          #+#    #+#             */
/*   Updated: 2018/03/28 08:04:03 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_H
# define KEY_H

# include "readline.h"

void	key_do_backspace(t_buffer *tbuffer);
void	key_do_home_end(t_buffer *tbuffer);
void	key_do_del(t_buffer *tbuffer);
void	key_do_shift_arrow(t_buffer *tbuffer);
void	key_do_arrow(t_buffer *tbuffer, t_cmd_hist **head);
void	key_group(t_buffer *tbuffer, t_cmd_hist **head);
#endif
