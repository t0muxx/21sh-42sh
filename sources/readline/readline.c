/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 07:58:24 by tmaraval          #+#    #+#             */
/*   Updated: 2018/02/22 16:04:18 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include <termcap.h>
#include <term.h>

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

void	readline_print_n_buf(int *cnt, char **buffer, char *c_buf)
{
	if (buffer[0][*cnt] != 0)
	{
		ft_putstr("\033[s");
		string_shift_right(buffer, *cnt);
		buffer[0][*cnt] = *c_buf;
		cursor_move_left(BUFFER_SIZE);
		readline_print_prompt();
		write(1, buffer[0], ft_strlen(buffer[0]));
		ft_putstr("\033[u");
		cursor_move_right(1);
	}
	else
		write(1, c_buf, 1);
	buffer[0][*cnt] = *c_buf;
	(*cnt)++;
}

/*
**  u_readline read STDIN char by char until enter is pressed
** it return a malloced string which must be freed later
*/

char	*readline(t_cmd_hist *head)
{
	char	c_buf;
	char	*buffer;
	int		cnt;

	cnt = 0;
	buffer = malloc(sizeof(char) * BUFFER_SIZE);
	ft_bzero(buffer, BUFFER_SIZE);
	while (read(0, &c_buf, 1) != -1)
	{
		if (c_buf == 127)
		{
			if (cnt > 0)
			{
				ft_putstr("\033[2K");
				cursor_move_left(1);
				ft_putstr("\033[s");
				cursor_move_left(BUFFER_SIZE);
				string_delete_char(&buffer, cnt - 1);
				readline_print_prompt();
				write(1, buffer, ft_strlen(buffer));
				ft_putstr("\033[u");
				cnt--;
			}
		}
		else if (c_buf == 27)
		{
			read(0, &c_buf, 1);
			//ft_printf("1 |%c|\n", c_buf);
			if (c_buf == '[')
			{
				read(0, &c_buf, 1);
				//ft_printf("2 |%c|\n", c_buf);
				if (c_buf == 'A')
					readline_history_print(&head, head->oldest, &cnt, &buffer);
				if (c_buf == 'B')
					readline_history_print(&head, head->newest, &cnt, &buffer);
				if (c_buf == 'C')
				{
					if (cnt < (int)ft_strlen(buffer))
					{
						cnt++;
						cursor_move_right(1);
					}
				}
				if (c_buf == 'D')
				{
					if (cnt > 0)
					{
						cnt--;
						cursor_move_left(1);
					}
				}
				if (c_buf == '3')
				{
					read(0, &c_buf, 1);
					//ft_printf("3 |%c|\n", c_buf);
					if (c_buf == '~')
					{
						//ft_printf("4 |%c|\n", c_buf);
						if (cnt < (int)ft_strlen(buffer))
						{
							ft_putstr("\033[2K");
							ft_putstr("\033[s");
							cursor_move_left(BUFFER_SIZE);
							string_delete_char(&buffer, cnt);
							readline_print_prompt();
							write(1, buffer, ft_strlen(buffer));
							ft_putstr("\033[u");
						}
					}
				}
			}
		}
		else if (c_buf == '\n')
		{
			if (ft_strlen(buffer) > 0)
				readline_history_add(buffer);
			break ;
		}
		else
			readline_print_n_buf(&cnt, &buffer, &c_buf);
	}
	return (buffer);
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
}
