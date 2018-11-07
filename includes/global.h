/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 11:25:35 by tmaraval          #+#    #+#             */
/*   Updated: 2018/11/07 15:16:57 by cormarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_H
# define GLOBAL_H
# define GLOBAL_BUF 128

# include "exec.h"

typedef struct	s_global
{
	char	*key;
	char	*value;
}				t_global;

extern int				g_stdio;
extern struct s_global	g_globals[128];

char			*global_replace(char *src, char *key, char *value);
void			insert_global(char *str, char ***env, int env_add);
int				g_replace_var(t_tkn **head, char *str, int index, char **env);
void			remove_global(char *str);
char			*get_global_key(char *value);
char			*get_global_value(char *key, char **env);
int				global_strlen(char *str, int index);
char			*global_concat(char *dest, char *value, int index, int len);
void			global_parsing(t_tkn **head, char ***env);

#endif
