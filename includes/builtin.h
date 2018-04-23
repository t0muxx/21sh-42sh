/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 11:19:08 by tmaraval          #+#    #+#             */
/*   Updated: 2018/04/23 09:19:36 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# define BUILTINNBR 6

typedef struct	s_builtin
{
	char	*name;
	int		(*addr)(char **, char ***);

}				t_builtin;

typedef struct	s_cd_opt
{
	int p;
	int l;
}				t_cd_opt;

void			builtin_get_builtin(t_builtin *builtin);
int				builtin_check_builtin(char **cmd, char ***myenv);
int				builtin_all(char **cmd, int nbr, char **myenv);

int				builtin_echo(char **cmd, char ***myenv);

int				builtin_cd_parse_opt(char *cmd, t_cd_opt *opt);
int				builtin_cd_home(char **myenv, char *pwd);
int				builtin_cd_dir(char *path, int print_dir);
int				builtin_cd_managechdir(char *pwd, char *path, t_cd_opt *opt,
	char **myenv);
int				builtin_cd_createpath(char *pwd, char *path, t_cd_opt *opt,
	char **myenv);
int				builtin_cd(char **cmd, char ***myenv);
int				builtin_cd_cdpath(char *pwd, char *path, char **myenv);
int				builtin_cd_dooldpwd(char *pwd, t_cd_opt *opt, char **myenv);

int				builtin_env(char **cmd, char ***myenv);
int				builtin_env_do(char **cmd, int *i);
char			**builtin_env_get_env(char **cmd, int *i);
int				builtin_env_do(char **cmd, int *i);

int				builtin_setenv(char **cmd, char ***myenv);

int				builtin_unsetenv(char **cmd, char ***myenv);

int				builtin_exit(char **cmd, char ***myenv);

#endif
