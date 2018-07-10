/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 08:54:21 by tmaraval          #+#    #+#             */
/*   Updated: 2018/07/10 08:58:37 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/types.h>
#include <sys/wait.h>

int		dup2_routine(int fd_dup, int io, int fd_close)
{
	close(fd_close);
	if (dup2(fd_dup, io) == -1)
		ft_putendl_fd("dup2 : failed to dup\n", 2);
	close(fd_dup);
	return (0);
}

int		close_routine(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
	return (0);
}

int		cpy_fd_routine(int dest[2], int src[2])
{
	dest[0] = src[0];
	dest[1] = src[1];
	return (0);
}

int		pipe_err_pipe(void)
{
	ft_putendl_fd("pipe : failed to pipe", 2);
	return (-1);
}

int		pipe_err_fork(void)
{
	ft_putendl_fd("fork : failed to fork", 2);
	return (-1);
}
