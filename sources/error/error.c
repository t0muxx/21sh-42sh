/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 16:35:26 by tmaraval          #+#    #+#             */
/*   Updated: 2018/02/02 13:43:15 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error_fork_err(void)
{
	char *str;

	str = "Error during fork\n";
	write(2, str, ft_strlen(str));
	exit(EXIT_FAILURE);
}

void	error_print_usage(char *usage)
{
	write(2, "Usage: ", 7);
	write(2, usage, ft_strlen(usage));
	write(2, "\n", 2);
}

void	error_print(int errnbr, char *func, char *arg)
{
	char *str;

	str = NULL;
	write(2, func, ft_strlen(func));
	write(2, ": ", 2);
	str = errnbr == 1 ? "undefined error" : str;
	str = errnbr == 2 ? "permission denied" : str;
	str = errnbr == 3 ? "no such file or directory" : str;
	str = errnbr == 4 ? "HOME is not defined" : str;
	str = errnbr == 5 ? "command not found" : str;
	str = errnbr == 6 ? "too many arguments" : str;
	str = errnbr == 7 ? "Variable name must contain \
	alphanumeric characters" : str;
	str = errnbr == 8 ? "too few arguments" : str;
	str = errnbr == 9 ? "Error during execve" : str;
	write(2, str, ft_strlen(str));
	if (ft_strlen(arg) != 0)
		write(2, ": ", 2);
	write(2, arg, ft_strlen(arg));
	write(2, "\n", 1);
}

void	error_malloc_err(void)
{
	write(2, "malloc error \n", 14);
	exit(EXIT_FAILURE);
}
