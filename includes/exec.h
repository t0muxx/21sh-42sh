/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 21:25:18 by cormarti          #+#    #+#             */
/*   Updated: 2018/09/17 18:29:40 by tomux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "parser.h"
# include "lexer.h"
# include "astree.h"

typedef struct s_node_type	t_node_type;

typedef	struct	s_pipeline
{
	t_astree *node;
	char **cmd;
	struct s_pipeline *next;

}		t_pipeline;

typedef struct	s_exec
{
	t_pipeline		*pipeline;
	t_nodetype	parent;
	t_list		*pids;
	int			last_exec;
	int			prec_exec;
	int		status;
	int		dont;

}				t_exec;

typedef int	(*t_node_fun)(t_astree *astree, char ***env, t_exec *exec);

struct	s_node_type
{
	t_nodetype		type;
	t_node_fun		fun;
};

extern t_node_type	node_fun[];

int		strdigit(char *str);
void		and_redir(t_tkn *tkn);
void		greatand_redir(t_tkn *tkn);
void		lessand_redir(t_tkn *tkn);
void		dless_redir(t_tkn *tkn);
int		is_redir(t_tkn_type type);
void		redirect_cmd(t_tkn *tkn);
int		node_ret(t_astree *astree);
int		exit_status(int status);
int		fork_and_exec(t_astree *astree, char ***env, t_exec *exec);
int		node_or_if(t_astree *astree, char ***env, t_exec *exec);
int		node_and(t_astree *astree, char ***env, int last_exec, t_exec *exec);
int		node_pipe(t_astree *astree, char ***env, t_exec *exec);
int		node_semi(t_astree *astree, char ***env, t_exec *exec);
int		node_and_if(t_astree *astree, char ***env, t_exec *exec);
int		is_redirected(t_tkn **tkn);
int		exec_cmd(t_astree *astree, char **env);
int		tkn_arr_len(t_tkn *tkn);
char		**lst_arr(t_tkn *tkn);
int		exec_node(t_astree *astree, char ***env, t_exec *exec);
int		child_process(t_astree *astree, char ***env);
char		*path_find_in_path(char *name, char **myenv);
int		check_exec_exception(t_exec *exec);
void		free_env(char **env);
void		free_astree(t_astree *astree);
void		pipeline_add(t_pipeline **last, t_pipeline *new);
t_pipeline	*pipeline_new(t_astree *astree);
void		pipeline_print(t_pipeline *head);
void	pipeline_free(t_pipeline *head);
int		path_exec_in(char *cmd, char **arg, char **env);
void		sig_child(void);
void		sig_father(void);
void		pids_add(t_exec *exec, pid_t pid);
void		sig_intercept_exec(t_exec *exec);

#endif
