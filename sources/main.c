/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 10:12:29 by tmaraval          #+#    #+#             */
/*   Updated: 2018/10/22 15:42:13 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "ext_globals.h"
#include "lexer.h"
#include "astree.h"
#include "exec.h"
#include "env.h"
#include "utils.h"

char	**do_read(t_buffer *tbuffer, char *line[2], char **env)
{
	tbuffer->head_hist = history_read(tbuffer->base_path);
	tbuffer->free_hist = tbuffer->head_hist;
	tbuffer_init(tbuffer, env);
	line[0] = readline(tbuffer);
	line[1] = 0;
	if (utils_in_quotes(tbuffer->buffer) == 0)
		line[0] = readline_mline(tbuffer);
	return (line);
}

void	do_read_simple(char *line[2],
		char ***env, t_tkn *tkn)
{
	get_next_line(0, &line[0]);
	line[1] = 0;
	if (ft_strlen(line[0]) > BUFFER_SIZE)
	{
		ft_putstr_fd("error : command too long\n", 2);
		exit(EXIT_FAILURE);
	}
	tkn = lex(&line[0], env);
	if (parse(tkn))
		do_ast_simple(tkn, env);
	free(line[0]);
	free_env(*env);
	exit(EXIT_SUCCESS);
}

void	main_loop(t_buffer *tbuffer, char *line[2], char ***env, t_tkn *tkn)
{
	do_read(tbuffer, line, *env);
	history_add(tbuffer->base_path, line[0]);
	ft_putstr("\n");
	tkn = lex(&line[0], env);
	free(line[0]);
	if (parse(tkn))
		do_ast(tkn, tbuffer, env);
	else
	{
		free_lst(tkn);
		free(tbuffer->termcap);
	}
	history_lst_free(tbuffer->free_hist);
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
		do_read_simple(line, &env, tkn);
	while (420)
		main_loop(&tbuffer, line, &env, tkn);
	free_globals();
	free_env(env);
}
