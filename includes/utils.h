/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 09:40:28 by tmaraval          #+#    #+#             */
/*   Updated: 2018/09/11 15:41:42 by tomux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "libft.h"
# include "readline.h"

# define PATH_ADD_SLASH 1
# define PATH_REM_SLASH 2

void	string_delete_char(char **str, int pos);
void	string_insert_substring(char **string, char *substring, int offset);
void	utils_delete_in_2darray(char **tabb, int index);
void	utils_free_2darray(void **array);
char	*make_path(char *curpath, char *dir);
int	make_path_find_last_slash(char *path);
void	make_path_manage_last_slash(char **path, int flg);
void	string_shift_right(char **str, int pos);
void	utils_free_cmd_hist(t_cmd_hist **head);
char	*string_concat_array(char **array);
int	utils_in_quotes(char *str);
char	*extract_current_word(char *str, int pos);
int	make_path_cnt_slash(char *str);
int	utils_is_dir(char *path);
#endif
