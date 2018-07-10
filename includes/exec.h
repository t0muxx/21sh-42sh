/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 21:25:18 by cormarti          #+#    #+#             */
/*   Updated: 2018/07/10 10:18:37 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "parser.h"
# include "lexer.h"
# include "astree.h"
# include "t_process.h"
# include <termios.h>

typedef struct s_node_type	t_node_type;

typedef struct	s_job
{
	char			*cmd;
	t_process		*first_process;
	pid_t			pgid;
	char			notified;
	struct	termios	tmodes;
	t_astree		*astree;
	struct s_job 	*next;

}				t_job;

typedef struct	s_exec
{
	int			newfds[2];
	int			oldfds[2];
	pid_t		pid;
	t_nodetype	parent;
	pid_t		pgid;
	int			last_exec;
	t_process	*first_pid;
	t_process	*process_pid;

}				t_exec;

typedef int	(*t_node_fun)(t_astree *astree, char **env, t_exec *exec);

struct	s_node_type
{
	t_nodetype		type;
	t_node_fun		fun;
};

extern t_node_type	node_fun[];

int		strdigit(char *str);
void	greatand_redir(t_tkn *tkn);
void	lessand_redir(t_tkn *tkn);
void	dless_redir(t_tkn *tkn);
int		is_redir(t_tkn_type type);
void	redirect_cmd(t_tkn *tkn);
int		node_ret(t_astree *astree);
int		exit_status(int status);
int		fork_and_exec(t_astree *astree, char **env);
int		node_or_if(t_astree *astree, char **env, t_exec *exec);
int		node_and(t_astree *astree, char **env, t_exec *exec);
int		node_pipe(t_astree *astree, char **env, t_exec *exec);
int		node_semi(t_astree *astree, char **env, t_exec *exec);
int		node_and_if(t_astree *astree, char **env, t_exec *exec);
int		is_redirected(t_tkn **tkn);
int		exec_cmd(t_astree *astree, char **env);
int		tkn_arr_len(t_tkn *tkn);
char	**lst_arr(t_tkn *tkn);
int		exec_node(t_astree *astree, char **env, t_exec *exec);
int		child_process(t_astree *astree, char **env);
char	*path_find_in_path(char *name, char **myenv);
int		check_exec_exception(t_exec *exec);
void	free_env(char **env);
void	free_astree(t_astree *astree);
void	free_tkn_lst(t_tkn *tkn);
int		dup2_routine(int fd_dup, int io, int fd_close);
int		close_routine(int fd[2]);
int		cpy_fd_routine(int dest[2], int src[2]);
int		pipe_err_pipe(void);
int		pipe_err_fork(void);

#endif
