/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 11:41:10 by tmaraval          #+#    #+#             */
/*   Updated: 2018/03/12 17:00:53 by tmaraval         ###   ########.fr       */
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

void	print_upd_tbuffer(t_buffer *tbuffer)
{
	int i;

	i = 0;
	while (tbuffer->buffer[i])
	{
		write(1, &(tbuffer->buffer[i]), 1);
		i++;
		if (tbuffer->index == tbuffer->colnbr - 1)
		{
			tbuffer->line++;
			tbuffer->index = -1;
			if (tbuffer->line == 2)
				tbuffer->colnbr += 3;
		}
		tbuffer->index++;
		tbuffer->cnt++;
	}
}

void	readline_print_n_buf(t_buffer *tbuffer)
{
	int		cur_index;
	int		cur_cnt;

	cur_index = 0;
	cur_cnt = 0;
	if (tbuffer->buffer[tbuffer->cnt] != 0)
	{
		cur_cnt = tbuffer->cnt;
		cur_index = tbuffer->index;
		string_shift_right(&(tbuffer->buffer), tbuffer->cnt);
		cursor_move_left_upd_tbuffer(BUFFER_SIZE, tbuffer);
		tbuffer->buffer[cur_cnt] = tbuffer->c_buf;
		readline_print_prompt();
		tbuffer->cnt = 0;
		tbuffer->index = 0;
		print_upd_tbuffer(tbuffer);
		tbuffer->index = (tbuffer->cnt % (tbuffer->colnbr + 1));
		cur_cnt++;
		//ft_printf("cnt = %d, index = %d, stlen = %d", tbuffer->cnt, tbuffer->index, (int)ft_strlen(tbuffer->buffer));
		cursor_move_left_upd_tbuffer(((int)ft_strlen(tbuffer->buffer) - cur_cnt), tbuffer);
		//cursor_move_right_upd_tbuffer(1, tbuffer);
	//ft_printf("\n|cnt = %d index = %d line = %d colnbr = %d|\n", tbuffer->cnt, tbuffer->index, tbuffer->line, tbuffer->colnbr);
	}
	else
	{
		write(1, &(tbuffer->c_buf), 1);
		if (tbuffer->index == tbuffer->colnbr - 1)
		{
			tbuffer->line++;
			tbuffer->index = -1;
			if (tbuffer->line == 2)
				tbuffer->colnbr += 3;
			tputs(tbuffer->termcap->sf, 0, ft_putcc);
		}
		tbuffer->index++;
		tbuffer->buffer[tbuffer->cnt] = tbuffer->c_buf;
		tbuffer->cnt++;
	}
}

/*
**  u_readline read STDIN char by char until enter is pressed
** it return a malloced string which must be freed later
*/

char	*readline(t_cmd_hist *head, t_term_cap *cur_termcap)
	{
	t_buffer	tbuffer;
	int			cur_cnt;
	int			cur_index;

	tbuffer.cnt = 0;
	tbuffer.index = 0;
	tbuffer.line = 1;
	tbuffer.buffer = malloc(sizeof(char) * BUFFER_SIZE);
	ft_bzero(tbuffer.buffer, BUFFER_SIZE);
	tbuffer.termcap = cur_termcap;
	while (read(0, &(tbuffer.c_buf), 1) != -1)
	{
		if (tbuffer.line == 1)
			tbuffer.colnbr = tgetnum("co") - 3;
		else
			tbuffer.colnbr = tgetnum("co");
		if (tbuffer.c_buf == 127)
		{
			if (tbuffer.cnt > 0)
			{
	//ft_printf("\n|cnt = %d index = %d line = %d colnbr = %d|\n", tbuffer.cnt, tbuffer.index, tbuffer.line, tbuffer.colnbr);
				cur_cnt = 0;
				cur_index = 0;
				cur_cnt = tbuffer.cnt;
				cur_index = tbuffer.index;
				cursor_move_left_upd_tbuffer(BUFFER_SIZE, &tbuffer);
				string_delete_char(&(tbuffer.buffer), cur_cnt - 1);
				tbuffer.cnt = (int)ft_strlen(tbuffer.buffer);
				if (tbuffer.line == 1)
					tbuffer.index = (tbuffer.cnt % (tbuffer.colnbr + 3 + 1));
				else
					tbuffer.index = (tbuffer.cnt % (tbuffer.colnbr + 1));
				tputs(tbuffer.termcap->cd, 0, ft_putcc);
				readline_print_prompt();
				write(1, tbuffer.buffer, ft_strlen(tbuffer.buffer));
		//ft_printf("cnt = %d stlen = %d", cur_cnt, (int)ft_strlen(tbuffer.buffer));
				cursor_move_left_upd_tbuffer(((int)ft_strlen(tbuffer.buffer) + 1) - cur_cnt, &tbuffer);
				//cursor_move_left_upd_tbuffer(1, &tbuffer);
			//	cursor_up_line((ft_strlen(tbuffer.buffer) / tbuffer.colnbr) - 1);
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
					 * 0 1 2 3 4 5 6 7 8
					 * 0 1 2 3 4 5 6 7 8
					 */
					if (tbuffer.cnt < (int)ft_strlen(tbuffer.buffer))
						cursor_move_right_upd_tbuffer(1, &tbuffer);
				}
				if (tbuffer.c_buf == 'D')
				{
					//ft_printf("%d", tbuffer.cnt);
					if (tbuffer.cnt > 0)
						cursor_move_left_upd_tbuffer(1, &tbuffer);
				}
				if (tbuffer.c_buf == '3')
				{
					read(0, &(tbuffer.c_buf), 1);
					if (tbuffer.c_buf == '~')
					{
						if (tbuffer.cnt < (int)ft_strlen(tbuffer.buffer))
						{
							//ft_putstr("\033[2K");
							//cursor_save_pos();
							//cursor_move_left(BUFFER_SIZE);
						//	ft_printf("\nkefiekofekofeofkeof\n");
							cur_cnt = 0;
							cur_index = 0;
							//temp = tgetstr("cd", NULL);
							cur_cnt = tbuffer.cnt;
							cur_index = tbuffer.index;
							string_delete_char(&(tbuffer.buffer), tbuffer.cnt);
							cursor_move_left_upd_tbuffer(BUFFER_SIZE, &tbuffer);
							tbuffer.cnt = (int)ft_strlen(tbuffer.buffer);
							if (tbuffer.line == 1)
								tbuffer.index = (tbuffer.cnt % (tbuffer.colnbr + 3 + 1));
							else
								tbuffer.index = (tbuffer.cnt % (tbuffer.colnbr + 1));
							tputs(tbuffer.termcap->cd, 0, ft_putcc);
							readline_print_prompt();
							write(1, tbuffer.buffer, ft_strlen(tbuffer.buffer));
							cursor_move_left_upd_tbuffer(((int)ft_strlen(tbuffer.buffer)) - cur_cnt, &tbuffer);
						//	cursor_reload_pos();
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
	t_term_cap		*cur_termcap;
	char			*line;
	t_cmd_hist		*head;
	
	cur_termcap = term_init();
	while (1)
	{
		readline_print_prompt();
		head = readline_history_read();
		line = readline(head, cur_termcap);
		ft_printf("\n|%s|\n", line);
		//free(line);
		ft_putstr("\n");
	}
}
