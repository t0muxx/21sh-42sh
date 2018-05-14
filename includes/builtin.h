/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 11:19:08 by tmaraval          #+#    #+#             */
/*   Updated: 2018/05/14 10:24:59 by tmaraval         ###   ########.fr       */
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

int				builtin_env(char **cmd, char ***myenv);
int				builtin_env_do(char **cmd, int *i);
char			**builtin_env_get_env(char **cmd, int *i);
int				builtin_env_do(char **cmd, int *i);

int				builtin_setenv(char **cmd, char ***myenv);

int				builtin_unsetenv(char **cmd, char ***myenv);

int				builtin_exit(char **cmd, char ***myenv);

#endif
