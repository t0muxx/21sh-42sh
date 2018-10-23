/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 09:57:42 by tmaraval          #+#    #+#             */
/*   Updated: 2018/10/15 10:20:10 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_gnl_buf_add(char **strr, char *buf, int ret)
{
	char *temp;

	buf[ret] = '\0';
	temp = *strr;
	*strr = ft_strjoin(*strr, buf);
	ft_strdel(&temp);
}

int		ft_do_last(char **strr, char **line, int *i)
{
	char	*temp;
	int		j;

	j = *i;
	if (ft_strlen(*strr) > 0)
	{
		while (strr[0][j])
		{
			if (strr[0][j] == '\n')
			{
				*line = ft_strsub(*strr, 0, j);
				temp = *strr;
				*strr = ft_strsub(*strr, j + 1, ft_strlen(*strr) - (j + 1));
				ft_strdel(&temp);
				return (1);
			}
			j++;
		}
		*line = ft_strsub(*strr, 0, ft_strlen(*strr));
		ft_strdel(strr);
		return (1);
	}
	return (0);
}

int		ft_gnl_do_lines(char **strr, char **line, int *i)
{
	int		j;
	char	*temp;

	j = *i;
	while (strr[0][j] != '\0')
	{
		if (strr[0][j] == '\n')
		{
			*line = ft_strsub(*strr, 0, j);
			temp = *strr;
			*strr = ft_strsub(*strr, j + 1, ft_strlen(*strr) - (j + 1));
			ft_strdel(&temp);
			return (1);
		}
		j++;
	}
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	int			ret;
	char		buf[BUFF_SIZE + 1];
	static char *strr;
	int			i;

	i = 0;
	if (fd < 0 || line == NULL || BUFF_SIZE <= 0)
		return (-1);
	if (strr == NULL)
		strr = ft_memalloc(1);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		ft_gnl_buf_add(&strr, buf, ret);
		if (ft_gnl_do_lines(&strr, line, &i) == 1)
			return (1);
	}
	if (ft_do_last(&strr, line, &i) == 1)
		return (1);
	if (ret == -1)
		return (-1);
	return (0);
}
