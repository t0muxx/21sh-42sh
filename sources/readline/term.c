/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 10:17:36 by tmaraval          #+#    #+#             */
/*   Updated: 2018/06/23 15:44:33 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include <termcap.h>
#include <term.h>

struct termios term;

void		term_get_colnbr(t_buffer *tbuffer)
{
	if (tbuffer->line == 1)
		tbuffer->colnbr = tgetnum("co") - 3;
	else if (tbuffer->state == READ_NORMAL)
		tbuffer->colnbr = tgetnum("co");
	else
		tbuffer->colnbr = tgetnum("co") - 2;
}

void		term_init_fill_cap(t_term_cap *termcap)
{
	if ((termcap->up = tgetstr("up", NULL)) == NULL)
		ft_printf("[ERR] 'up' may not work in this terminal\n");
	if ((termcap->ce = tgetstr("ce", NULL)) == NULL)
		ft_printf("[ERR] 'ce'  may not work in this terminal\n");
	if ((termcap->le = tgetstr("le", NULL)) == NULL)
		ft_printf("[ERR] 'le'  may not work in this terminal\n");
	if ((termcap->nd = tgetstr("nd", NULL)) == NULL)
		ft_printf("[ERR] 'nd'  may not work in this terminal\n");
	if ((termcap->sc = tgetstr("sc", NULL)) == NULL)
		ft_printf("[ERR] 'sc'  may not work in this terminal\n");
	if ((termcap->rc = tgetstr("rc", NULL)) == NULL)
		ft_printf("[ERR] 'rc'  may not work in this terminal\n");
	if ((termcap->sf = tgetstr("sf", NULL)) == NULL)
		ft_printf("[ERR] 'sf'  may not work in this terminal\n");
	if ((termcap->co = tgetnum("co")) == -1)
		ft_printf("[ERR] 'co'  may not work in this terminal\n");
	if ((termcap->cd = tgetstr("cd", NULL)) == NULL)
		ft_printf("[ERR] 'cd'  may not work in this terminal\n");
	if ((termcap->so = tgetstr("so", NULL)) == NULL)
		ft_printf("[ERR] 'so'  may not work in this terminal\n");
	if ((termcap->se = tgetstr("se", NULL)) == NULL)
		ft_printf("[ERR] 'se'  may not work in this terminal\n");
}

t_term_cap	*term_init_cap(void)
{
	t_term_cap *termcap;

	if (!(termcap = malloc(sizeof(*termcap))))
		error_malloc_err();
	term_init_fill_cap(termcap);
	return (termcap);
}

t_term_cap	*term_init(char **env)
{
	t_term_cap		*termcap;
	char			*term_name;

	termcap = NULL;
	term_name = env_get_var("TERM", env);
	if (term_name == NULL)
		term_name = ft_strdup("xterm-256color");
	tgetent(NULL, term_name);
	tcgetattr(0, &term);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSADRAIN, &term);
	termcap = term_init_cap();
	free(term_name);
	return (termcap);
}

void		term_close()
{
	tcgetattr(0, &term);
	term.c_lflag |= (ICANON | ECHO | ECHOCTL | ISIG);
	tcsetattr(0, 0, &term);
}
