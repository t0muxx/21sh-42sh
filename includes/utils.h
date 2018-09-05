/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 09:40:28 by tmaraval          #+#    #+#             */
/*   Updated: 2018/09/05 14:52:15 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "libft.h"
# include "readline.h"

# define PATH_ADD_SLASH 1
# define PATH_REM_SLASH 2

void	string_delete_char(char **str, int pos);
void	utils_delete_in_2darray(char **tabb, int index);
void	utils_free_2darray(void **array);
char	*make_path(char *curpath, char *dir);
int		make_path_find_last_slash(char *path);
void	string_shift_right(char **str, int pos);
void	utils_free_cmd_hist(t_cmd_hist **head);
char	*string_concat_array(char **array);
int		utils_in_quotes(char *str);
char	*extract_current_word(char *str, int pos);
#endif
