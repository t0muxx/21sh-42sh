/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_print.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 08:30:14 by tmaraval          #+#    #+#             */
/*   Updated: 2018/09/12 09:32:53 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <sys/ioctl.h>
#include <sys/types.h>
#include "readline.h"
#include "completion.h"

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
	char	*word;
	int		i;
	char	*substring;
	int		last_slash;
	int		slash_cnt;

	word = extract_current_word(tbuffer->buffer, tbuffer->cnt);
	slash_cnt = make_path_cnt_slash(word);
	last_slash = make_path_find_last_slash(word);
	if (word[0] != '/' && slash_cnt != 0)
		i = ft_strlen(word) - last_slash - 1;
	else if (word[0] == '/' && slash_cnt == 1)
		i = ft_strlen(word) - 1;
	else if (word[0] == '/')
		i = ft_strlen(word) - last_slash - 1;
	else
		i = ft_strlen(word);
//	ft_printf("i = |%d|\n", i);
	substring = (char *)(filelist->content + i);
//	ft_printf("substring = |%s|\n", substring);
	string_insert_substring(&tbuffer->buffer, substring, tbuffer->cnt);
//	ft_printf("tbuffer = |%s|\n", tbuffer->buffer);
	free(word);
	line_reset(tbuffer);
	cursor_move_right(tbuffer, ft_strlen(substring));
}

void	completion_print_several(t_list *filelist)
{
	int wordbycol;
	int	maxlen;
	int i;

	maxlen = completion_print_get_max_len(filelist);
	wordbycol = completion_print_get_word_by_cols(maxlen);
	ft_putendl("");
	while (filelist)
	{
		i = 0;
		while (filelist && i < wordbycol - 1)
		{
			ft_printf("%s", filelist->content);
			completion_print_space(maxlen, (int)ft_strlen(filelist->content));
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
