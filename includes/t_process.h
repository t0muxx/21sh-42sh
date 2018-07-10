/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_process.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 13:12:50 by tmaraval          #+#    #+#             */
/*   Updated: 2018/07/10 10:18:16 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_PROCESS_H
# define T_PROCESS_H 

#include <sys/types.h>
#include <sys/wait.h>

typedef struct s_process
{
	char **argv;
	pid_t pid;
	char completed;
	char stopped;
	t_nodetype parent;
	int	newfds[2];
	int	oldfds[2];
	int status;
	struct s_process *next;
}				t_process;

t_process		*t_process_new(pid_t pid);
void		t_process_add(t_process **last, t_process *new);
void			t_process_free(t_process *list);

#endif
