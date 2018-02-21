/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_readline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 15:04:07 by tmaraval          #+#    #+#             */
/*   Updated: 2018/02/21 10:08:45 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
# include <termcap.h>
# include <term.h>

/* u_readline read STDIN char by char until enter is pressed */
/* it return a malloced string which must be freed later 	*/
char	*u_readline()
{
	char	c_buf;
	char	*buffer;
	int		cnt;

	cnt = 0;
	buffer = malloc(sizeof(char) * BUFFER_SIZE);
	ft_bzero(buffer, BUFFER_SIZE);
	while (read(0, &c_buf, 1) != -1)
	{
		if (c_buf == 27)
		{
			read(0, &c_buf, 1);
			if (c_buf == '[')
			{
				read(0, &c_buf, 1);
				if (c_buf == 'A')
				{
					ft_printf("UP KEY PRESSED\n");
				}
			}
		}
		else if (c_buf == '\n')
		{
			buffer[cnt] = 0;
			readline_history_add(buffer);
			break ;
		}
		else
		{
			write(1, &c_buf, 1);
			buffer[cnt] = c_buf;
			cnt++;
		}
	}
	return (buffer);
}

int		main(void)
{
	extern char	**environ;
	struct termios term;
	char	*term_name;
	char	*line;

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
		line = u_readline();
		ft_printf("|%s|\n", line);
		free(line);	
	}
}
