/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 11:19:08 by tmaraval          #+#    #+#             */
/*   Updated: 2018/05/15 17:18:56 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# define BUILTINNBR 6

# define CD_L		2
# define CD_P		3
# define CD_OPTERR  -1
# define CD_NOOPT	0

typedef struct	s_builtin
{
	char	*name;
	int		(*addr)(char **, char ***);

}				t_builtin;

void			builtin_get_builtin(t_builtin *builtin);
int				builtin_check_builtin(char **cmd, char ***myenv);
int				builtin_all(char **cmd, int nbr, char **myenv);

int				builtin_echo(char **cmd, char ***myenv);

int				builtin_env(char **cmd, char ***myenv);
int				builtin_env_do(char **cmd, int *i);
char			**builtin_env_get_env(char **cmd, int *i);
int				builtin_env_do(char **cmd, int *i);

int				builtin_setenv(char **cmd, char ***myenv);

int				builtin_unsetenv(char **cmd, char ***myenv);

int				builtin_exit(char **cmd, char ***myenv);

int		builtin_cd(char **cmd, char ***env);
int				cd_parse_opt(char **cmd);
int				cd_check_opt(char *opt);
int				cd_skip_opt(char **cmd);
#endif
