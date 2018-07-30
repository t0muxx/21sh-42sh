/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomux </var/mail/tomux>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 16:34:50 by tomux             #+#    #+#             */
/*   Updated: 2018/07/30 17:24:38 by tomux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h" 
#include "lexer.h"
#include "astree.h"
#include "exec.h"
#include "env.h"


void		ast_set_parent(t_astree *astree)
{
	t_nodetype tmp;

	tmp = -2;
	while (astree)
	{
		astree->parent = tmp;
		tmp = astree->type;
		astree = astree->left;
	}
}

void		ast_set_rootpipe(t_astree *astree)
{
	int rootpipe;

	rootpipe = 1;
	while (astree)
	{
		rootpipe = 1;
		
		while (astree && astree->type != NT_PIPE)
		{
			astree = astree->left;
		}
		while (astree && astree->type == NT_PIPE)
		{
			astree->root_pipe = rootpipe;
			rootpipe = 0;
			astree = astree->left;
		}

	}
}

void		print_ast(t_astree *astree)
{
	char **cmd;

	if (astree == NULL)
		return ;
	print_ast(astree->left);
	ft_printf("type = ");
	switch(astree->type)
	{
		case 1: ft_printf("PIPE"); break;
		case 2: ft_printf("SEMI"); break;
		case 3: ft_printf("CMD"); break;
		case 4: ft_printf("AND"); break;
		case 5: ft_printf("OR_IF"); break;
		case 6: ft_printf("AND_IF"); break;

	}
	ft_putstr(" ");
	cmd = lst_arr(astree->arg);
	ft_printf("cmd = |%s| ", cmd[0]);
	ft_printf("parent = |%d |", astree->parent);
	ft_printf("root_pipe = |%d|\n", astree->root_pipe);
	print_ast(astree->right);
}

char		**do_read(t_buffer *tbuffer, char *line[2], char **env)
{
	t_cmd_hist		*head;

	
	tbuffer->head_hist = history_read();
	tbuffer->cur_hist = NULL;
	tbuffer_init(tbuffer, env);
	line[0] = readline(tbuffer);
	line[1] = 0;
	return (line);
}

void		do_ast(t_tkn *tkn, t_buffer *tbuffer, char ***env)
{
	t_astree		*astree;
	
	while (tkn->next)
	{
		if (tkn->next->type == CHR_NEWLINE)
			break ;
		tkn = tkn->next;
	}
	tkn->next = NULL;
	astree = ast_build(tkn);
	term_close();
	free(tbuffer->termcap);
	ast_set_parent(astree);
	ast_set_rootpipe(astree);
//	print_ast(astree);
	child_process(astree, env);
	free_astree(astree);
}

void		do_ast_simple(t_tkn *tkn, char **env)
{
	t_astree		*astree;
	
	while (tkn->next)
	{
		if (tkn->next->type == CHR_NEWLINE)
			break ;
		tkn = tkn->next;
	}
	tkn->next = NULL;
	astree = ast_build(tkn);
	ast_set_parent(astree);
	ast_set_rootpipe(astree);
	child_process(astree, &env);
	free_astree(astree);
}

int		main(void)
{
	char			*line[2];
	t_buffer		tbuffer;
	char			**env;
	t_tkn			*tkn;

	env = env_create_copy();
	if (isatty(0) == 0)
	{
	//	ft_putendl_fd("not connected to a terminal", 2);
		get_next_line(0, &line[0]);
		line[1] = 0;
		if (ft_strlen(line[0]) > BUFFER_SIZE)
		{
			ft_putstr_fd("error : command too long\n", 2);
			exit(EXIT_FAILURE);
		}
		tkn = lex(&line[0]);
		if (parse(tkn))
			do_ast_simple(tkn, env);
		free_tkn_lst(tkn);
		free(line[0]);
		free_env(env);
		exit(-1);
	}
	while (420)
	{
		do_read(&tbuffer, line, env);
		history_add(line[0]);
		ft_putstr("\n");
		tkn = lex(&line[0]);
		if (parse(tkn))
			do_ast(tkn, &tbuffer, &env);
		free_tkn_lst(tkn);
		history_lst_free(tbuffer.head_hist);
		free(line[0]);
	}
	free_env(env);
}
