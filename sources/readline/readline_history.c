/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_history.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 09:15:03 by tmaraval          #+#    #+#             */
/*   Updated: 2018/02/21 09:51:18 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

/* readline_history_add add command at the end 	*/
/* of the file .history 						*/ 

void	readline_history_add(char *cmd)
{
	int	fd;

	if (access(HISTORY_FILE, F_OK) != 1)
	{
		if ((fd = open(HISTORY_FILE, O_WRONLY | O_CREAT)) == -1)
			ft_printf("ERROR UNKNOW\n");
		close(fd);
		if ((fd = open(HISTORY_FILE, O_WRONLY | O_APPEND)) == -1)
			ft_printf("ERROR UNKNOW\n");
	}
	else
	{
		if ((fd = open(HISTORY_FILE, O_WRONLY | O_APPEND)) == -1)
			ft_printf("ERROR UNKNOW\n");
	}
//	write(1, cmd, ft_strlen(cmd));
	write(fd, cmd, ft_strlen(cmd));
	write(fd, "\n", 1);
	close(fd);
}
