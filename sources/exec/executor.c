/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomux </var/mail/tomux>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 15:07:10 by tomux             #+#    #+#             */
/*   Updated: 2018/07/05 17:36:30 by tomux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "astree.h"
#include "exec.h"

int	executor(t_astree **astree, char **env)
{
	t_job *job;
	t_process *process;

	job = (t_job *)ft_memalloc(sizeof(t_job));
	process = (t_process *)ft_memalloc(sizeof(t_process));
	job->astree = *astree;
	job->astree->is_root_node = 1;
	job->first_process = process;
	exec_node(job, process, env);
}
