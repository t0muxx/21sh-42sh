/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_readline.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 08:27:02 by tmaraval          #+#    #+#             */
/*   Updated: 2018/03/15 08:48:20 by tmaraval         ###   ########.fr       */
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
# include "utils.h"

# define BUFFER_SIZE 2048
# define HISTORY_FILE ".history"
# define ERASE_LINE "\033[2K"
# define SAVE_CURSOR "\033[s"
# define LOAD_CURSOR "\033[u"


/* The double linked list for history 		*/
/* read from the file (oldest to newest) 	*/
/* its added to the linked list like 		*/
/* [new]->[new -1]->[etc..]->NULL 			*/
/* next = oldest and prev = newest     		*/

typedef struct				s_cmd_hist
{
	char					*cmd;
	struct s_cmd_hist		*oldest;
	struct s_cmd_hist		*newest;

}							t_cmd_hist;

typedef struct				s_term_cap
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

}							t_term_cap;

typedef struct				s_buffer
{
	char		*buffer;
	char		c_buf;
	int			cnt;
	int			index;
	int			line;
	int			colnbr;
	t_term_cap 	*termcap;

}							t_buffer;

char	*env_get_var(char *name, char **myenv);

char			*readline(t_cmd_hist *head, t_term_cap *cur_termcap);
t_cmd_hist		*readline_history_read(void);
void			readline_history_add(char *cmd);
void			readline_history_print(t_cmd_hist **head, t_cmd_hist *next, t_buffer *tbuffer);
int				readline_print_prompt(int print);
void			readline_print_upd_tbuffer(t_buffer *tbuffer);
void			readline_print_n_buf(t_buffer *tbuffer);

t_cmd_hist		*history_lst_new(char *cmd);
void			history_lst_add(t_cmd_hist **head, t_cmd_hist *new);

t_term_cap		*term_init_cap();
t_term_cap 		*term_init();
void			term_close();
#endif
