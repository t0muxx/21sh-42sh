/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 03:20:55 by cormarti          #+#    #+#             */
/*   Updated: 2018/06/23 15:36:02 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/astree.h"
#include "../../includes/exec.h"
#include "utils.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void	fd_status(int pipefd[2])
{
	pid_t pid;

	pid = getpid();
	dprintf(2, " ########## fd status ###########\n");
	dprintf(2, "in pid %d\n", pid);
	dprintf(2, "fd[0] = %d\n", pipefd[0]);
	if (fcntl(pipefd[0], F_GETFD) == -1)
	{
		perror("fcntl");
	}
	else
	{
		ft_printf("open\n");
	}
	dprintf(2, "fd[1] = %d\n", pipefd[1]);
	if (fcntl(pipefd[1], F_GETFD) == -1)
	{
		perror("fcntl");
	}
	else
	{
		ft_printf("open\n");
	}
	dprintf(2, "##########################\n");

}

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

int		pipe_routine(t_astree *astree, char **env, t_exec *exec)
{
	int newfds[2];
	int status;
	int status2;
	pid_t pid;
	pid_t pid2;
	t_process *new;
	
	if (astree->left->type != NT_PIPE)
	{
		if (pipe(newfds) == -1)
		{
			ft_putendl_fd("pipe : failed to pipe", 2);
			return (-1);
		}
		if ((pid = fork()) == -1)
		{
			ft_putendl_fd("fork : failed to fork", 2);
			return (-1);
		}
		else if (pid == 0)
		{
	//		dprintf(2, "Child left pid = %d ppid = %d pgid = %d\n", getpid(), getppid(), getpgid(0));
			dup2_routine(newfds[1], 1, newfds[0]);
			exec_cmd(astree->left, env);
		}
		else
		{
	//		dprintf(2, "Pere left pid = %d ppid = %d pgid = %d\n", getpid(), getppid(), getpgid(0));
			new = t_process_new(pid);
			t_process_add(&(exec->process_pid), new);
			close(newfds[1]);
			cpy_fd_routine(exec->oldfds, newfds);
		}
	}
	if (pipe(newfds) == -1)
	{
		ft_putendl_fd("pipe : failed to pipe", 2);
		return (-1);
	}
	if ((pid2 = fork()) == -1)
	{
		ft_putendl_fd("fork : failed to fork", 2);
		return (-1);
	}
	else if (pid2 == 0)
	{
	//	dprintf(2, "fils right pid = %d ppid = %d pgid = %d\n", getpid(), getppid(), getpgid(0));
		new = t_process_new(getpid());
		t_process_add(&(exec->process_pid), new);	
		dup2_routine(exec->oldfds[0], 0, exec->oldfds[1]);
		if (astree->is_root_node == 0)
			dup2_routine(newfds[1], 1, newfds[0]);
		exec_cmd(astree->right, env);
	}
	else
	{
	//	dprintf(2, "Pere right pid = %d ppid = %d pgid = %d\n", getpid(), getppid(), getpgid(0));
		new = t_process_new(pid2);
		t_process_add(&(exec->process_pid), new);
		if (astree->is_root_node == 0)
		{
			close(newfds[1]);
			cpy_fd_routine(exec->oldfds, newfds);
		}
		else
		{
			close_routine(newfds);
			while (waitpid(-1, &status, 0) > 0)
			{
			//	dprintf(2, "WEXITSTATUS = %d\n", WEXITSTATUS(status));
				if (WEXITSTATUS(status) == EXIT_FAILURE)
				{
					close(exec->oldfds[0]);
					close(exec->oldfds[1]);
					while (exec->process_pid->next != NULL)
					{
			//			dprintf(2, "kill %d\n", exec->process_pid->pid);
						kill((pid_t)exec->process_pid, SIGKILL);
						exec->process_pid = exec->process_pid->next;
					}
					waitpid((exec->process_pid->pid), &status2, 0);
					exit(EXIT_FAILURE);
			//		dprintf(2, "fini de wait\n");
					return (-1);
				}
			}
			close_routine(exec->oldfds);
		}
	}
	return (0);
}

int		node_pipe(t_astree *astree, char **env, int last_exec, t_exec *exec)
{
	pipe_routine(astree, env, exec);
	return (0);
}
