/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 11:41:10 by tmaraval          #+#    #+#             */
/*   Updated: 2018/03/14 21:25:32 by tomlulu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include <termcap.h>
#include <term.h>
#include "cursor.h"

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

char	*readline(t_cmd_hist *head, t_term_cap *cur_termcap)
	{
	t_buffer	tbuffer;
	int			cur_cnt;
	char		buf[4];

	tbuffer.cnt = 0;
	tbuffer.index = 0;
	tbuffer.line = 1;
	tbuffer.buffer = malloc(sizeof(char) * BUFFER_SIZE);
	ft_bzero(tbuffer.buffer, BUFFER_SIZE);
	ft_bzero(buf, 4);
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
				cur_cnt = tbuffer.cnt;
				cursor_move_left_upd_tbuffer(BUFFER_SIZE, &tbuffer);
				string_delete_char(&(tbuffer.buffer), cur_cnt - 1);
				tputs(tbuffer.termcap->cd, 0, ft_putcc);
				readline_print_prompt(TRUE);
				tbuffer.cnt = 0;
				tbuffer.index = 0;
				readline_print_upd_tbuffer(&tbuffer);
				cur_cnt--;
				cursor_move_left_upd_tbuffer(((int)ft_strlen(tbuffer.buffer)) - cur_cnt, &tbuffer);
				//cursor_move_left_upd_tbuffer(1, &tbuffer);
			//	cursor_up_line((ft_strlen(tbuffer.buffer) / tbuffer.colnbr) - 1);
			}
		}
		// touche home [H
		// touch end [F
		else if (tbuffer.c_buf == 27)
		{
			read(0, &(tbuffer.c_buf), 1);
			//ft_putchar(tbuffer.c_buf);
			if (tbuffer.c_buf == '[')
			{
				read(0, &(tbuffer.c_buf), 1);
				//ft_putchar(tbuffer.c_buf);
				if (tbuffer.c_buf == '1')
				{
					read(0, buf, 3);
					if (buf[0] == ';' && buf[1] == '2' && buf[2] == 'A')
					{
						if (tbuffer.line > 1)
						{
							if (tbuffer.cnt < tbuffer.colnbr)
								cursor_move_left_upd_tbuffer(tbuffer.cnt, &tbuffer);
							else
								cursor_move_left_upd_tbuffer(tbuffer.colnbr, &tbuffer);
						}						
					}
					if (buf[0] == ';' && buf[1] == '2' && buf[2] == 'B')
					{
						if (tbuffer.cnt + tbuffer.colnbr < (int)ft_strlen(tbuffer.buffer))
							cursor_move_right_upd_tbuffer(tbuffer.line == 1 ? tbuffer.colnbr + 3 : tbuffer.colnbr, &tbuffer);
						else
							cursor_move_right_upd_tbuffer((int) ft_strlen(tbuffer.buffer), &tbuffer);
					}
					if (buf[0] == ';' && buf[1] == '2' && buf[2] == 'D')
					{
						cursor_move_left_next_word(&tbuffer);
						ft_bzero(buf, 4);	
					}
					if (buf[0] == ';' && buf[1] == '2' && buf[2] == 'C')
					{
						cursor_move_right_next_word(&tbuffer);
						ft_bzero(buf, 4);	
					}
				}
				if (tbuffer.c_buf == 'A')
					readline_history_print(&head, head->oldest, &tbuffer);
				if (tbuffer.c_buf == 'B')
					readline_history_print(&head, head->newest, &tbuffer);
				if (tbuffer.c_buf == 'C')
				{
					if (tbuffer.cnt < (int)ft_strlen(tbuffer.buffer))
						cursor_move_right_upd_tbuffer(1, &tbuffer);
				}
				if (tbuffer.c_buf == 'D')
				{
					if (tbuffer.cnt > 0)
						cursor_move_left_upd_tbuffer(1, &tbuffer);
				}
				if (tbuffer.c_buf == 'H')
				{
					cursor_move_left_upd_tbuffer(tbuffer.cnt, &tbuffer);
					tbuffer.cnt = 0;
					tbuffer.index = 0;
				}
				if (tbuffer.c_buf == 'F')
					cursor_move_right_upd_tbuffer((int)ft_strlen(tbuffer.buffer) - tbuffer.cnt, &tbuffer);
				if (tbuffer.c_buf == '3')
				{
					read(0, &(tbuffer.c_buf), 1);
					if (tbuffer.c_buf == '~')
					{
						if (tbuffer.cnt < (int)ft_strlen(tbuffer.buffer))
						{
							cur_cnt = 0;
							cur_cnt = tbuffer.cnt;
							string_delete_char(&(tbuffer.buffer), tbuffer.cnt);
							cursor_move_left_upd_tbuffer(BUFFER_SIZE, &tbuffer);
							tputs(tbuffer.termcap->cd, 0, ft_putcc);
							readline_print_prompt(TRUE);
							tbuffer.cnt = 0;
							tbuffer.index = 0;
							readline_print_upd_tbuffer(&tbuffer);
							cursor_move_left_upd_tbuffer(((int)ft_strlen(tbuffer.buffer)) - cur_cnt, &tbuffer);
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
