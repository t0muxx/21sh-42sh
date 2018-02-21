/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_readline.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 08:27:02 by tmaraval          #+#    #+#             */
/*   Updated: 2018/02/21 11:17:08 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_H
# define READLINE_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "libft.h"
# include "get_next_line.h"
# include "error.h"

# define BUFFER_SIZE 2048
# define HISTORY_FILE ".history"

/* The double linked list for history 		*/
/* read from the file (oldest to newest) 	*/
/* its added to the linked list like 		*/
/* [new]->[new -1]->[etc..]->NULL 			*/
/* next = oldest and prev = newest     		*/

typedef struct				s_cmd_hist
{
	char					*cmd;
	struct s_cmd_hist		*oldest;
	struct s_cmd_hist		*newest;

}							t_cmd_hist;

char	*env_get_var(char *name, char **myenv);

void			readline_history_add(char *cmd);
t_cmd_hist		*readline_history_read(void);

t_cmd_hist		*history_lst_new(char *cmd);
void			history_lst_add(t_cmd_hist **head, t_cmd_hist *new);
#endif
