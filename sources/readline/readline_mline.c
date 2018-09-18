/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_mline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 09:40:52 by tmaraval          #+#    #+#             */
/*   Updated: 2018/09/18 09:52:10 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "utils.h"
#include <sys/ioctl.h>

void	*readline_mline_get_func_array(void)
{
	void	(**fptr)(t_buffer *, char *);

	fptr = malloc(sizeof(void (*)(t_buffer *, char *)) * 11);
	fptr[0] = input_arrow_left;
	fptr[1] = input_arrow_right;
	fptr[2] = insert_char;
	fptr[3] = input_enter_mline;
	fptr[4] = input_backspace;
	fptr[5] = input_delete;
	fptr[6] = input_home;
	fptr[7] = input_end;
	fptr[8] = input_ctrl_d;
	fptr[9] = input_tab;
	fptr[10] = NULL;
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
	tbuffer->ctrlc = 0;
	tbuffer->state = READ_NORMAL;
	tbuffer->buffer = malloc(sizeof(char) * BUFFER_SIZE);
	ft_bzero(tbuffer->buffer, BUFFER_SIZE);
	ft_bzero(tbuffer->cutbuffer, BUFFER_SIZE);
	tbuffer->termcap = termcap;
}

void	readline_mline_loop(t_buffer *mlbuffer, char *read_buf,
void (**fptr)(t_buffer *, char *))
{
	int				i;
	struct winsize	w;
	int				fd;

	fd = 0;
	while (mlbuffer->state != READ_PROCESS && mlbuffer->ctrlc != 1)
	{
		i = 0;
		ioctl(0, TIOCGWINSZ, &w);
		mlbuffer->colnbr = w.ws_col;
		dup2(0, fd);
		mlbuffer->saved_in = dup(0);
		read(0, read_buf, MAX_KEYCODE_SIZE);
		while (fptr[i])
		{
			(fptr[i])(mlbuffer, read_buf);
			i++;
		}
		ft_bzero(read_buf, MAX_KEYCODE_SIZE);
	}
	if (mlbuffer->ctrlc == 1)
		dup2(mlbuffer->saved_in, 0);
}

void	readline_mline_do(t_buffer *tbuffer, t_buffer *mlbuffer,
void (**fptr)(t_buffer *, char *), char *read_buf)
{
	sig_intercept_ml(tbuffer, mlbuffer);
	mlbuffer_init(mlbuffer, tbuffer->termcap);
	ft_putstr("\n> ");
	readline_mline_loop(mlbuffer, read_buf, fptr);
	mlbuffer->state = READ_NORMAL;
	ft_strcat(tbuffer->buffer, mlbuffer->buffer);
	ft_bzero(mlbuffer->buffer, BUFFER_SIZE);
	free(mlbuffer->buffer);
}

char	*readline_mline(t_buffer *tbuffer)
{
	char		*read_buf;
	void		(**fptr)(t_buffer *, char *);
	t_buffer	mlbuffer;
	int			last;

	if (!(read_buf = malloc(sizeof(char) * MAX_KEYCODE_SIZE)))
		return (NULL);
	ft_bzero(read_buf, MAX_KEYCODE_SIZE);
	if ((last = ft_strlen(tbuffer->buffer)) > 0)
	{
		if (tbuffer->buffer[last - 1] != '\\')
			ft_strncat(tbuffer->buffer, "\n", 1);
	}
	fptr = readline_mline_get_func_array();
	mlbuffer.env = tbuffer->env;
	while (tbuffer->cnt <= BUFFER_SIZE &&
	utils_in_quotes(tbuffer->buffer) == 0 && tbuffer->ctrlc != 1)
		readline_mline_do(tbuffer, &mlbuffer, fptr, read_buf);
	if (ft_strlen(tbuffer->buffer) != 0)
		tbuffer->buffer[ft_strlen(tbuffer->buffer) - 1] = '\0';
	free(fptr);
	free(read_buf);
	return (tbuffer->buffer);
}
