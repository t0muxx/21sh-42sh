/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_process.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 13:12:50 by tmaraval          #+#    #+#             */
/*   Updated: 2018/06/23 15:47:26 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_PROCESS_H
# define T_PROCESS_H 

#include <sys/types.h>
#include <sys/wait.h>

typedef struct s_process
{
	pid_t pid;
	struct s_process *next;

}				t_process;


t_process		*t_process_new(pid_t pid);
void		t_process_add(t_process **last, t_process *new);
void			t_process_free(t_process *list);

#endif
