/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 10:17:36 by tmaraval          #+#    #+#             */
/*   Updated: 2018/03/29 11:51:53 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include <termcap.h>
#include <term.h>

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

t_term_cap	*term_init(void)
{
	t_term_cap		*termcap;
	struct termios	term;
	char			*term_name;
	extern char		**environ;

	termcap = NULL;
	term_name = env_get_var("TERM", environ);
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

void		term_close(void)
{
	struct termios	term;
	char			*term_name;
	extern char		**environ;

	term_name = env_get_var("TERM", environ);
	tgetent(NULL, term_name);
	tcgetattr(0, &term);
	term.c_lflag = (ICANON | ECHO);
	tcsetattr(0, TCSADRAIN, &term);
}
