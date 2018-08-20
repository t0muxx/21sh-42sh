/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 10:12:29 by tmaraval          #+#    #+#             */
/*   Updated: 2018/08/20 11:09:22 by tomux            ###   ########.fr       */
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
	tbuffer->head_hist = history_read(tbuffer->base_path);
	tbuffer->cur_hist = NULL;
	tbuffer_init(tbuffer, env);
	line[0] = readline(tbuffer);
	line[1] = 0;
	return (line);
}

void		do_read_simple(char *line[2],
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
	exit(EXIT_SUCCESS);
}

void		create_base_path(t_buffer *tbuffer)
{
	ft_bzero(tbuffer->base_path, 1024);
	getcwd(tbuffer->base_path, 1024);
	ft_strcat(tbuffer->base_path, "/.history");
}

void		increment_shlvl(char ***env)
{
	char	*shlvl;
	int 	i_shlvl;

	i_shlvl = 0;
	if ((shlvl = env_get_var("SHLVL", *env)) == NULL)
		return ;
	i_shlvl = ft_atoi(shlvl);
	i_shlvl++;
	free(shlvl);
	shlvl = ft_itoa(i_shlvl);
	env_update_var("SHLVL", shlvl, *env);
	free(shlvl);
}

int		main(void)
{
	char			*line[2];
	t_buffer		tbuffer;
	char			**env;
	t_tkn			*tkn;

	tkn = NULL;
	env = env_create_copy();
	increment_shlvl(&env);
	create_base_path(&tbuffer);	
	if (isatty(0) == 0)
		do_read_simple(line, env, tkn);
	while (420)
	{
		do_read(&tbuffer, line, env);
		history_add(tbuffer.base_path, line[0]);
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
