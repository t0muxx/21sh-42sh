/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomux </var/mail/tomux>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 16:34:50 by tomux             #+#    #+#             */
/*   Updated: 2018/07/23 16:42:35 by tomux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h" 
#include "lexer.h"
#include "astree.h"
#include "exec.h"
#include "env.h"

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

void		do_ast(t_tkn *tkn, t_buffer *tbuffer, char **env)
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
	child_process(astree, env);
	free_astree(astree);
}

int		main(void)
{
	char			*line[2];
	t_buffer		tbuffer;
	char			**env;
	t_tkn			*tkn;

	env = env_create_copy();
	while (420)
	{
		do_read(&tbuffer, line, env);
		history_add(line[0]);
		ft_putstr("\n");
		tkn = lex(&line[0]);
		if (parse(tkn))
			do_ast(tkn, &tbuffer, env);
		free_tkn_lst(tkn);
		history_lst_free(tbuffer.head_hist);
		free(line[0]);
	}
	free_env(env);
}
