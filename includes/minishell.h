/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 11:02:37 by tmaraval          #+#    #+#             */
/*   Updated: 2018/02/19 12:40:23 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include "libft/libft.h"
# include "get_next_line.h"
# include "builtin.h"
# include "error.h"
# include "env.h"
# include "ps1.h"

# define PROMPT " minishell:"

char	*path_find_in_path(char *name, char **myenv);
int		path_exec_in(char *cmd, char **arg, char **env);

void	utils_free_2darray(void **array);
void	utils_print_2dtab(char **tab);
char	*utils_makepath(char *pwd, char *directory);
void	utils_delete_in_2darray(char **tab, int index);
void	sig_intercept();
int		utils_str_is_empty(const char *str);
void	utils_makepath_cpy(char *pwd, char *directory, char *abspath);
#endif
