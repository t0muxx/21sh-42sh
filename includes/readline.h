/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_readline.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 08:27:02 by tmaraval          #+#    #+#             */
/*   Updated: 2018/08/21 11:03:57 by tomux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_H
# define READLINE_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "libft.h"
# include "get_next_line.h"
# include "error.h"
# include <term.h>

# define BUFFER_SIZE 2048
# define MAX_KEYCODE_SIZE 6
# define HISTORY_FILE ".history"
# define FT_KEY_UP "\033[A"
# define FT_KEY_DOWN "\033[B"
# define FT_KEY_LEFT "\033[D"
# define FT_KEY_RIGHT "\033[C"
# define FT_KEY_DEL "\033[3~"
# define FT_KEY_HOME "\033[H"
# define FT_KEY_END "\033[F"
# define FT_KEY_SHIFT_UP "\033[1;2A"
# define FT_KEY_SHIFT_DOWN "\033[1;2B"
# define FT_KEY_SHIFT_LEFT "\033[1;2D"
# define FT_KEY_SHIFT_RIGHT "\033[1;2C"
# define FT_KEY_ALT_RIGHT "\033\033[C"
# define FT_KEY_ALT_LEFT "\033\033[D"
# define FT_KEY_CTRL_X "^X"
# define FT_KEY_CTRL_K "^K"
# define FT_KEY_CTRL_P "^P"
# define FT_KEY_CTRL_D "^D"
# define FT_KEY_CTRL_C "^C"

/*
** The double linked list for history
** read from the file (oldest to newest)
** its added to the linked list like
** [new]->[new -1]->[etc..]->NULL
** next = oldest and prev = newest
*/

enum e_readline_state
{
	READ_IN_QUOTE,
	READ_NORMAL,
	READ_ERROR,
	READ_PROCESS,
	READ_MULTI,

};

typedef struct	s_cmd_hist
{
	char					*cmd;
	struct s_cmd_hist		*oldest;
	struct s_cmd_hist		*newest;

}				t_cmd_hist;

typedef struct	s_term_cap
{
	char	*up;
	char	*ce;
	char	*le;
	char	*nd;
	char	*sc;
	char	*rc;
	char	*sf;
	int		co;
	char	*cd;
	char	*so;
	char	*se;

}				t_term_cap;

typedef struct	s_buffer
{
	char		*buffer;
	char		base_path[1024];
	char		reset;
	char		cutbuffer[BUFFER_SIZE];
	char		c_buf;
	int			cnt;
	int			index;
	int			line;
	int			colnbr;
	int			prompt_len;
	int			cutstart;
	int			cutend;
	int			curs_pos;
	int			state;
	int			mline;
	t_term_cap	*termcap;
	t_cmd_hist	*head_hist;
	t_cmd_hist	*cur_hist;

}				t_buffer;

void			sig_intercept(t_buffer *tbuffer);
void		sig_intercept_ml(t_buffer *tbuffer, t_buffer *mlbuffer);

void			input_arrow_left(t_buffer *tbuffer, char *read_buf);
void			input_arrow_right(t_buffer *tbuffer, char *read_buf);
void			input_arrow_up(t_buffer *tbuffer, char *read_buf);
void			input_arrow_down(t_buffer *tbuffer, char *read_buf);
void			input_backspace(t_buffer *tbuffer, char *read_buf);
void			input_delete(t_buffer *tbuffer, char *read_buf);
void			input_home(t_buffer *tbuffer, char *read_buf);
void			input_end(t_buffer *tbuffer, char *read_buf);
void			input_arrow_shift_updown(t_buffer *tbuffer, char *read_buf);
void			input_shift_right_left(t_buffer *tbuffer, char *read_buf);
void			input_select_right(t_buffer *tbuffer, char *read_buf);
void			input_select_left(t_buffer *tbuffer, char *read_buf);
void			input_cut(t_buffer *tbuffer, char *read_buf);
void			input_paste(t_buffer *tbuffer, char *read_buf);
void			input_copy(t_buffer *tbuffer, char *read_buf);
void			input_enter(t_buffer *tbuffer, char *read_buf);
void			line_go_down(t_buffer *tbuffer, int cnt);
void			input_ctrl_d(t_buffer *tbuffer, char *read_buf);
void			input_ctrl_c(t_buffer *tbuffer, char *read_buf);
void			insert_char(t_buffer *tbuffer, char *read_buf);
void			insert_tbuffer(t_buffer *tbuffer);
void			prompt_print(t_buffer *tbuffer);
void			line_go_begin(t_buffer *tbuffer);
void			line_go_end(t_buffer *tbuffer);
void			line_reset(t_buffer *tbuffer);
void			cursor_move_left(t_buffer *tbuffer, int cnt);
void			cursor_save_pos(t_buffer *tbuffer);
void			cursor_reload_pos(t_buffer *tbuffer);
void			cursor_move_right(t_buffer *tbuffer, int cnt);
void			cursor_move_left_next_word(t_buffer *tbuffer);
void			cursor_move_right_next_word(t_buffer *tbuffer);
t_cmd_hist		*history_read(char *base_path);
void			history_print(t_buffer *tbuffer, t_cmd_hist **toprint);
void			history_print_reset(t_buffer *tbuffer);
t_cmd_hist		*history_lst_new(char *cmd);
void			history_lst_add(t_cmd_hist **head, t_cmd_hist *new);
void			history_add(char *base_path, char *cmd);
void			history_lst_free(t_cmd_hist *head);
char			*env_get_var(char *name, char **myenv);
char			*readline(t_buffer *tbuffer);
void			tbuffer_init(t_buffer *tbuffer, char **env);
char			*readline_mline(t_buffer *tbuffer);
void			input_enter_mline(t_buffer *tbuffer, char *read_buf);
t_term_cap		*term_init_cap();
void			term_get_colnbr(t_buffer *tbuffer);
t_term_cap		*term_init(char **env);
void			term_close();
int		ft_putcc(int c);
#endif
