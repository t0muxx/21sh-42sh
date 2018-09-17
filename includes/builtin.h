/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 11:19:08 by tmaraval          #+#    #+#             */
/*   Updated: 2018/09/17 10:59:23 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include "lexer.h"
# include "astree.h"

# define BUILTINNBR 6

# define CD_L		2
# define CD_P		3
# define CD_OPTERR  -1
# define CD_NOOPT	0

typedef struct	s_builtin
{
	char	*name;
	int		(*addr)(char **, char ***, t_buffer *);

}				t_builtin;

void			builtin_get_builtin(t_builtin *builtin);
int				builtin_check_builtin(t_astree *astree, char **cmd, char ***myenv, t_buffer *tbuffer);
int				builtin_all(char **cmd, int nbr, char **myenv, t_buffer *tbuffer);
int				builtin_echo(char **cmd, char ***myenv, t_buffer *tbuffer);
int				builtin_env(char **cmd, char ***myenv,t_buffer *tbuffer);
int				builtin_env_do(char **cmd, int *i);
char			**builtin_env_get_env(char **cmd, int *i);
int				builtin_env_do(char **cmd, int *i);
int				builtin_setenv(char **cmd, char ***myenvi, t_buffer *tbuffer);
int				builtin_unsetenv(char **cmd, char ***myenv,t_buffer *tbuffer);
int				builtin_exit(char **cmd, char ***myenv, t_buffer *tbuffer);
int				builtin_cd(char **cmd, char ***env, t_buffer *tbuffer);
int				cd_err_chdir(char *dir);
int				cd_change_dir_p(char *oldpwd, char *pwd,
char *dir, char ***env);
int				cd_change_dir_dash(char *oldpwd, char **dir, char ***env);
int				cd_change_dir_gen(char *oldpwd, char **pwd,
char *dir, char ***env);
int				cd_parse_opt(char **cmd);
int				cd_check_opt(char *opt);
int				cd_skip_opt(char **cmd);
#endif
