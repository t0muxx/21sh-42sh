/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_print.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 08:30:14 by tmaraval          #+#    #+#             */
/*   Updated: 2018/09/07 16:08:11 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <sys/ioctl.h>
#include <sys/types.h>
#include "readline.h"

int		completion_print_get_max_len(t_list *filelist)
{
	int max;

	max = 0;
	while (filelist)
	{
		if (max < (int )ft_strlen(filelist->content))
			max = ft_strlen(filelist->content);
		filelist = filelist->next;
	}
	return (max);
}

/*
 * tant que ((maxlen + 2) * x) - colnbr) > 3
 * x++
 *
*/
int		completion_print_get_word_by_cols(int maxlen)
{
	int	wordbycol;
	int colnbr;
	struct winsize w;

	ioctl(0, TIOCGWINSZ, &w);	
	colnbr = w.ws_col;
//	ft_printf("colnbr = |%d|\n", colnbr);
//	ft_printf("maxlen = |%d|\n", maxlen);
	wordbycol = 1;
	while (((colnbr - 2) - ((maxlen + 2) * wordbycol)) > 2)
		wordbycol++;
	if (((colnbr - 2) - ((maxlen + 2) * wordbycol)) < 0)
		wordbycol--;
//	ft_printf("ordbycol = |%d|\n", wordbycol);
	return (wordbycol);
}

void	completion_print_space(int maxlen, int len)
{
	while (len < maxlen)
	{
		ft_putstr(" ");
		len++;
	}
}

int		completion_get_filelist_nbr(t_list *filelist)
{
	int i;

	i = 0;
	while (filelist)
	{
		i++;
		filelist = filelist->next;
	}
	return (i);
}

void	completion_insert_char(t_buffer *tbuffer, t_list *filelist)
{
	char *word;
	int i;
	char *substring;

	word = extract_current_word(tbuffer->buffer, tbuffer->cnt);
	i = ft_strlen(word);
	substring = (char *)(filelist->content + i);
	string_insert_substring(&tbuffer->buffer,  substring, tbuffer->cnt);
	free(word);
	line_reset(tbuffer);
	cursor_move_right(tbuffer, ft_strlen(substring));
}

void	completion_print_several(t_list *filelist)
{
	int wordbycol;
	int	maxlen;
	int i;

	i = 0;
	maxlen = completion_print_get_max_len(filelist);
	wordbycol = completion_print_get_word_by_cols(maxlen);
	ft_putendl("");
	while (filelist)
	{
		i = 0;
		while (filelist && i < wordbycol - 1)
		{
			ft_printf("%s", filelist->content);
			completion_print_space(maxlen , (int)ft_strlen(filelist->content));
			ft_putstr("  ");
			i++;
			filelist = filelist->next;
		}
		if (filelist != NULL)
		{
			ft_printf("%s", filelist->content);
			filelist = filelist->next;
		}
		ft_putendl("");
	}
}

void	completion_print(t_buffer *tbuffer, t_list *filelist)
{
	if (completion_get_filelist_nbr(filelist) > 1)
		completion_print_several(filelist);
	else if (completion_get_filelist_nbr(filelist) == 1)
		completion_insert_char(tbuffer, filelist);
	line_reset(tbuffer);
}
