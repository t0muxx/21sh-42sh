/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 09:23:36 by tmaraval          #+#    #+#             */
/*   Updated: 2018/09/07 10:17:01 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPLETION_H
# define COMPLETION_H 
int		completion_in_first_word(char *userinput, int pos);
t_list *completion_read(char **dirs);
t_list *completion_cmp_userinput_filelist(char *userinput, t_list *filelist);
void	completion_print(t_buffer *tbuffer, t_list *filelist);
char	*completion_trim_get_str_to_complete(char *userinput);
char	*completion_trim_get_searchdir(char *userinput);
void	completion_trim_append_slash(t_list *filelist, char *searchdir);

#endif
