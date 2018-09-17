/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 13:50:48 by tmaraval          #+#    #+#             */
/*   Updated: 2018/09/17 11:39:57 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "utils.h"

int		builtin_exit(char **cmd, char ***myenv, t_buffer *tbuffer)
{
	int		i;

	i = 0;
	if (tbuffer)
		history_add(tbuffer->base_path, tbuffer);
	while (cmd[i])
		i++;
	if (i == 1)
	{
		utils_free_2darray((void **)*myenv);
		term_close();
		exit(EXIT_SUCCESS);
	}
	else
		exit(ft_atoi(cmd[1]));
	return (0);
}
