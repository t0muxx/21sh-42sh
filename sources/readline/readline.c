/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 07:58:24 by tmaraval          #+#    #+#             */
/*   Updated: 2018/02/28 09:22:14 by tomlulu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include <termcap.h>
#include <term.h>
#include "cursor.h"

void	readline_print_prompt(void)
{
	ft_putstr("$> ");
}

/*
** readline_print_n_buf manage if its the last char on the line
** it print it and add it to the buffer
** if its not the last char it will shift the buffer on the right
** in order to get a blank space for the char to add (line edition)
*/

void	readline_print_n_buf(t_buffer *tbuffer)
{
	if (tbuffer->buffer[tbuffer->cnt] != 0)
	{

		cursor_save_pos();
		string_shift_right(&(tbuffer->buffer), tbuffer->cnt);
		tbuffer->buffer[tbuffer->cnt] = tbuffer->c_buf;
		readline_print_prompt();
		write(1, tbuffer->buffer, ft_strlen(tbuffer->buffer));
		cursor_reload_pos();
		cursor_move_right(1, tbuffer);
	}
	else
	{
		tbuffer->index++;
		if (tbuffer->index == tbuffer->colnbr)
		{
			tbuffer->line++;
			tbuffer->index = 0;
			if (tbuffer->line == 2)
				tbuffer->colnbr += 3;
		}
		write(1, &(tbuffer->c_buf), 1);
	}
	tbuffer->buffer[tbuffer->cnt] = tbuffer->c_buf;
	tbuffer->cnt++;
}

/*
**  u_readline read STDIN char by char until enter is pressed
** it return a malloced string which must be freed later
*/

char	*readline(t_cmd_hist *head)
	{
	t_buffer	tbuffer;
	
	tbuffer.colnbr = tgetnum("co") - 3;
	tbuffer.cnt = 0;
	tbuffer.index = 1;
	tbuffer.line = 1;
	tbuffer.buffer = malloc(sizeof(char) * BUFFER_SIZE);
	ft_bzero(tbuffer.buffer, BUFFER_SIZE);
	while (read(0, &(tbuffer.c_buf), 1) != -1)
	{
		if (tbuffer.c_buf == 127)
		{
			if (tbuffer.cnt > 0)
			{
				ft_putstr("\033[2K");
				cursor_move_left(1);
				cursor_save_pos();
				cursor_move_left(BUFFER_SIZE);
				string_delete_char(&(tbuffer.buffer), tbuffer.cnt - 1);
				readline_print_prompt();
				write(1, tbuffer.buffer, ft_strlen(tbuffer.buffer));
				cursor_reload_pos();
				tbuffer.cnt--;
			}
		}
		else if (tbuffer.c_buf == 27)
		{
			read(0, &(tbuffer.c_buf), 1);
			//ft_printf("1 |%c|\n", c_buf);
			if (tbuffer.c_buf == '[')
			{
				read(0, &(tbuffer.c_buf), 1);
				//ft_printf("2 |%c|\n", c_buf);
				if (tbuffer.c_buf == 'A')
					readline_history_print(&head, head->oldest, &tbuffer);
				if (tbuffer.c_buf == 'B')
					readline_history_print(&head, head->newest, &tbuffer);
				if (tbuffer.c_buf == 'C')
				{
					/*
					 * 0 1 2 3 4 5 6 7 8
					 * 9 1011121314151617
					 * 1 2 3 4 5 6 7 8 9
					 * 1 2 3 4 5 6 7 8 9
					 * 101112131415161718 -> line = 2
					 * 192021222324252627 -> line = 3
					 */
					if (tbuffer.cnt < (int)ft_strlen(tbuffer.buffer))
					{
						tbuffer.cnt++;
						cursor_move_right(1, &tbuffer);
					}
				}
				if (tbuffer.c_buf == 'D')
				{
					//ft_printf("%d", tbuffer.cnt);
					if (tbuffer.cnt > 0)
					{
						tbuffer.cnt--;
						cursor_move_left_upd_tbuffer(1, &tbuffer);
					}
				}
				if (tbuffer.c_buf == '3')
				{
					read(0, &(tbuffer.c_buf), 1);
					if (tbuffer.c_buf == '~')
					{
						if (tbuffer.cnt < (int)ft_strlen(tbuffer.buffer))
						{
							ft_putstr("\033[2K");
							cursor_save_pos();
							cursor_move_left(BUFFER_SIZE);
							string_delete_char(&(tbuffer.buffer), tbuffer.cnt);
							readline_print_prompt();
							write(1, tbuffer.buffer, ft_strlen(tbuffer.buffer));
							cursor_reload_pos();
						}
					}
				}
			}
		}
		else if (tbuffer.c_buf == '\n')
		{
			if (ft_strlen(tbuffer.buffer) > 0)
				readline_history_add(tbuffer.buffer);
			break ;
		}
		else
			readline_print_n_buf(&tbuffer);
	
	//ft_printf("\n|cnt = %d index = %d line = %d colnbr = %d|\n", tbuffer.cnt, tbuffer.index, tbuffer.line, tbuffer.colnbr);
	}
	return (tbuffer.buffer);
}

int		main(void)
{
	extern char		**environ;
	struct termios	term;
	char			*term_name;
	char			*line;
	t_cmd_hist		*head;

	term_name = env_get_var("TERM", environ);
	tgetent(NULL, term_name);
	tcgetattr(0, &term);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSADRAIN, &term);
	while (1)
	{
		readline_print_prompt();
		head = readline_history_read();
		line = readline(head);
		ft_printf("\n|%s|\n", line);
		free(line);
		ft_putstr("\n");
	}
	term.c_lflag = (ICANON | ECHO);
	tcsetattr(0, TCSADRAIN, &term);
}
