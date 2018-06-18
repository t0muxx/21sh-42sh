/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 10:17:36 by tmaraval          #+#    #+#             */
/*   Updated: 2018/06/18 11:32:45 by tomlulu          ###   ########.fr       */
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

t_term_cap	*term_init_cap(void)
{
	t_term_cap *termcap;

	if (!(termcap = malloc(sizeof(*termcap))))
		error_malloc_err();
	if ((termcap->up = tgetstr("up", NULL)) == NULL)
		ft_printf("[ERR] 'up' capability may not work in this terminal\n");
	if ((termcap->ce = tgetstr("ce", NULL)) == NULL)
		ft_printf("[ERR] 'ce' capability may not work in this terminal\n");
	if ((termcap->le = tgetstr("le", NULL)) == NULL)
		ft_printf("[ERR] 'le' capability may not work in this terminal\n");
	if ((termcap->nd = tgetstr("nd", NULL)) == NULL)
		ft_printf("[ERR] 'nd' capability may not work in this terminal\n");
	if ((termcap->sc = tgetstr("sc", NULL)) == NULL)
		ft_printf("[ERR] 'sc' capability may not work in this terminal\n");
	if ((termcap->rc = tgetstr("rc", NULL)) == NULL)
		ft_printf("[ERR] 'rc' capability may not work in this terminal\n");
	if ((termcap->sf = tgetstr("sf", NULL)) == NULL)
		ft_printf("[ERR] 'sf' capability may not work in this terminal\n");
	if ((termcap->co = tgetnum("co")) == -1)
		ft_printf("[ERR] 'co' capability may not work in this terminal\n");
	if ((termcap->cd = tgetstr("cd", NULL)) == NULL)
		ft_printf("[ERR] 'cd' capability may not work in this terminal\n");
	if ((termcap->so = tgetstr("so", NULL)) == NULL)
		ft_printf("[ERR] 'so' capability may not work in this terminal\n");
	if ((termcap->se = tgetstr("se", NULL)) == NULL)
		ft_printf("[ERR] 'se' capability may not work in this terminal\n");
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
	return (termcap);
}

void		term_close(char **env)
{
	tcgetattr(0, &term);
	term.c_lflag |= (ICANON | ECHO | ECHOCTL | ISIG);
	tcsetattr(0, 0, &term);
}
