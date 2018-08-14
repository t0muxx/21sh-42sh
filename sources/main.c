/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 10:12:29 by tmaraval          #+#    #+#             */
/*   Updated: 2018/08/14 10:20:26 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "lexer.h"
#include "astree.h"
#include "exec.h"
#include "env.h"

void		print_ast(t_astree *astree)
{
	char **cmd;

	if (astree == NULL)
		return ;
	print_ast(astree->left);
	ft_printf("type = ");
	switch (astree->type)
	{
		case -2: ft_printf("NT_ROOT"); break;
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
	tbuffer->head_hist = history_read();
	tbuffer->cur_hist = NULL;
	tbuffer_init(tbuffer, env);
	line[0] = readline(tbuffer);
	line[1] = 0;
	return (line);
}

void		do_read_simple(t_buffer *tbuffer, char *line[2],
char **env, t_tkn *tkn)
{
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
	exit(EXIT_SUCCESS);
}

int		main(void)
{
	char			*line[2];
	t_buffer		tbuffer;
	char			**env;
	t_tkn			*tkn;

	env = env_create_copy();
	if (isatty(0) == 0)
		do_read_simple(&tbuffer, line, env, tkn);
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
