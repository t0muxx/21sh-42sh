/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 11:41:10 by tmaraval          #+#    #+#             */
/*   Updated: 2018/03/15 09:33:44 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include <termcap.h>
#include <term.h>
#include "cursor.h"
#include "key.h"

/*
*******************************************************************************
********************************************************************************
** Here is the readline main file.
** It use a tbuffer struct (declared in readline.h)
** which uses three different int to know the cursor position in the shell.
** the colnbr which give us the number of colon in the term
** the index parameter who tell us where we are in the colunm.
** it is reseted whenever we go down a line ex (with 10 colunm) :
**
** $ >   0 1 2 3 4 5 6
** 0 1 2 3 4 5 6 7 8 9
** 0 1 2 3 4 5 6 7 8 9
**
** the cnt parameter give us where we are in the buffer string.
** it isn't reseted. Ex :
** $ >   0 1 2 3 4 5 6
** 7 8 9 10111213141516
** 17181920212223242526
**
** In all function we check if we are in line 1 
** if yes we need to take in count the prompt len.
********************************************************************************
********************************************************************************
*/

/*
**  u_readline read STDIN char by char until enter is pressed
** it return a malloced string which must be freed later
*/

void	readline_main_loop(t_buffer *tbuffer, t_cmd_hist *head)
{
	while (read(0, &(tbuffer->c_buf), 1) != -1)
	{
		if (tbuffer->line == 1)
			tbuffer->colnbr = tgetnum("co") - 3;
		else
			tbuffer->colnbr = tgetnum("co");
		if (tbuffer->c_buf == 127)
			key_do_backspace(tbuffer);
		else if (tbuffer->c_buf == 27)
			key_group(tbuffer, head);
		else if (tbuffer->c_buf == '\n')
		{
		if (ft_strlen(tbuffer->buffer) > 0)
				readline_history_add(tbuffer->buffer);
			break ;
		}
		else
			readline_print_n_buf(tbuffer);
	}
}

char	*readline(t_cmd_hist *head, t_term_cap *cur_termcap)
{
	t_buffer	tbuffer;
	int			prompt_len;

	tbuffer.cnt = 0;
	tbuffer.index = 0;
	tbuffer.line = 1;
	tbuffer.buffer = malloc(sizeof(char) * BUFFER_SIZE);
	ft_bzero(tbuffer.buffer, BUFFER_SIZE);
	tbuffer.termcap = cur_termcap;
	prompt_len = readline_print_prompt(FALSE);
	readline_main_loop(&tbuffer, head);	
	//ft_printf("\n|cnt = %d index = %d line = %d colnbr = %d|\n", tbuffer.cnt, tbuffer.index, tbuffer.line, tbuffer.colnbr);
	return (tbuffer.buffer);
}


int		main(void)
{
	t_term_cap		*cur_termcap;
	char			*line;
	t_cmd_hist		*head;
//	char			temp;
	
	cur_termcap = term_init();
	while (1)
	{
		readline_print_prompt(TRUE);
		head = readline_history_read();
		line = readline(head, cur_termcap);
		//read(0, &temp, 1);
		//ft_printf("%c\n", temp);
		ft_printf("\n|%s|\n", line);
		ft_putstr("\n");
	}
}
