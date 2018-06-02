/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 09:40:28 by tmaraval          #+#    #+#             */
/*   Updated: 2018/06/02 15:47:20 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "libft.h"
# include "readline.h"

# define PATH_ADD_SLASH 1
# define PATH_REM_SLASH 2

void	string_delete_char(char **str, int pos);
char	*make_path(char *curpath, char *dir);
void	string_shift_right(char **str, int pos);
int		ft_putcc(int c);
void	utils_free_cmd_hist(t_cmd_hist **head);
#endif
