/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 09:23:36 by tmaraval          #+#    #+#             */
/*   Updated: 2018/09/18 10:02:44 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPLETION_H
# define COMPLETION_H

int			completion_in_first_word(char *userinput, int pos);
t_list		*completion_read(char **dirs);
t_list		*completion_cmp_userinput_filelist(char *userinput,
t_list *filelist);
void		completion_print(t_buffer *tbuffer, t_list *filelist);
char		*completion_trim_get_str_to_complete(char *userinput);
char		*completion_trim_get_searchdir(char *userinput);
void		completion_trim_append_slash(t_list *filelist, char **searchdir);
int			completion_print_get_max_len(t_list *filelist);
int			completion_print_get_word_by_cols(int maxlen);
void		completion_print_space(int maxlen, int len);
void		completion_search_in_path(t_buffer *tbuffer, char **env);
void		completion_search_in_dir(t_buffer *tbuffer, char *userinput);
int			completion_find_lastcmd(char *userinput, int pos);

#endif
