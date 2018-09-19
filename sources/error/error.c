/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 16:35:26 by tmaraval          #+#    #+#             */
/*   Updated: 2018/09/19 08:41:15 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "stdarg.h"

void	error_invalid_opt(char *opt)
{
	char *str;

	str = ": invalid option\n";
	write(2, opt, ft_strlen(opt));
	write(2, str, ft_strlen(str));
}

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
	str = errnbr == 10 ? "OLDPWD not set" : str;
	str = errnbr == 11 ? "Not a directory" : str;
	str = errnbr == 12 ? "Cannot be opened" : str;
	write(2, str, ft_strlen(str));
	if (ft_strlen(arg) != 0)
		write(2, ": ", 2);
	write(2, arg, ft_strlen(arg));
	write(2, "\n", 1);
}

void	error_malloc_err(int nbarg, ...)
{
	int		i;
	va_list	ap;
	void	*ptr;

	i = 0;
	va_start(ap, nbarg);
	write(2, "malloc error \n", 14);
	while (i < nbarg)
	{
		ptr = va_arg(ap, void *);
		free(ptr);
		i++;
	}
	va_end(ap);
	exit(EXIT_FAILURE);
}
