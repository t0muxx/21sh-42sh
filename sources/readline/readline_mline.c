/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_mline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 09:40:52 by tmaraval          #+#    #+#             */
/*   Updated: 2018/09/04 09:42:01 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "utils.h"
#include <sys/ioctl.h>

void	*readline_mline_get_func_array(void)
{
	void	(**fptr)(t_buffer *, char *);

	fptr = malloc(sizeof(void (*)(t_buffer *, char *)) * 10);
	fptr[0] = input_arrow_left;
	fptr[1] = input_arrow_right;
	fptr[2] = insert_char;
	fptr[3] = input_enter_mline;
	fptr[4] = input_backspace;
	fptr[5] = input_delete;
	fptr[6] = input_home;
	fptr[7] = input_end;
	fptr[8] = input_ctrl_d;
	fptr[9] = NULL;
	return (fptr);
}

void	mlbuffer_init(t_buffer *tbuffer, t_term_cap *termcap)
{
	tbuffer->cnt = 0;
	tbuffer->prompt_len = 2;
	tbuffer->index = 0;
	tbuffer->line = 1;
	tbuffer->cutstart = 0;
	tbuffer->colnbr = tgetnum("co");
	tbuffer->cutend = 0;
	tbuffer->mline = 1;
	tbuffer->state = READ_NORMAL;
	tbuffer->buffer = malloc(sizeof(char) * BUFFER_SIZE);
	ft_bzero(tbuffer->buffer, BUFFER_SIZE);
	ft_bzero(tbuffer->cutbuffer, BUFFER_SIZE);
	tbuffer->termcap = termcap;
}

void	readline_mline_loop(t_buffer *mlbuffer, char *read_buf,
void (**fptr)(t_buffer *, char *))
{
	int		i;
	struct	winsize w;

	while (mlbuffer->state != READ_PROCESS)
	{
		i = 0;
		ioctl(0, TIOCGWINSZ, &w);
		mlbuffer->colnbr = w.ws_col;
		read(0, read_buf, MAX_KEYCODE_SIZE);
		while (fptr[i])
		{
			(fptr[i])(mlbuffer, read_buf);
			i++;
		}
		ft_bzero(read_buf, MAX_KEYCODE_SIZE);
	}
}

char	*readline_mline(t_buffer *tbuffer)
{
	char 		*read_buf;
	void 		(**fptr)(t_buffer *, char *);
	t_buffer	mlbuffer;

	if (!(read_buf = malloc(sizeof(char) * MAX_KEYCODE_SIZE)))
		return (NULL);
	ft_bzero(read_buf, MAX_KEYCODE_SIZE);
	ft_strncat(tbuffer->buffer, "\n", 1);
	fptr = readline_mline_get_func_array();
	while (tbuffer->cnt <= BUFFER_SIZE && utils_in_quotes(tbuffer->buffer) == 0)
	{
		sig_intercept_ml(tbuffer, &mlbuffer);
		mlbuffer_init(&mlbuffer, tbuffer->termcap); 
		ft_putstr("\n> ");
		readline_mline_loop(&mlbuffer, read_buf, fptr);
		mlbuffer.state = READ_NORMAL;
		ft_strcat(tbuffer->buffer, mlbuffer.buffer);
		ft_bzero(mlbuffer.buffer, BUFFER_SIZE);
		free(mlbuffer.buffer);
	}
	tbuffer->buffer[ft_strlen(tbuffer->buffer) - 1] = '\0';
	free(fptr);
	free(read_buf);
	return (tbuffer->buffer);
		
}
