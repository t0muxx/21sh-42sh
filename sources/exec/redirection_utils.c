/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 09:05:59 by tmaraval          #+#    #+#             */
/*   Updated: 2018/10/24 09:07:15 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	less_redir_err(char *file, int fd)
{
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	close(fd);
	exit(EXIT_FAILURE);
}
