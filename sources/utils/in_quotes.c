/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 09:52:48 by tmaraval          #+#    #+#             */
/*   Updated: 2018/10/11 11:57:11 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline.h>

void	proceed_in_loop(char chr, int *quote, int *dquote, char *last)
{
	if (chr == '"' && *dquote == 0 && *quote == 0)
	{
		*dquote = 1;
		*last = '"';
	}
	else if (chr == '"' && *dquote == 1 && *last == '"')
	{
		*dquote = 0;
		*last = 0;
	}
	if (chr == '\'' && *quote == 0 && *dquote == 0)
	{
		*quote = 1;
		*last = '\'';
	}
	else if (chr == '\'' && *quote == 1 && *last == '\'')
	{
		*quote = 0;
		*last = 0;
	}
}

int		utils_in_quotes_ret(int quote, int dquote, int i, char *str)
{
	if ((dquote == 0 && quote == 0) == 1)
	{
		if ((i = ft_strlen(str)) > 0)
		{
			if (str[i - 1] == '\\')
				return (0);
		}
		return (1);
	}
	else
		return (0);
}

int		utils_in_quotes(char *str)
{
	int		i;
	int		quote;
	int		dquote;
	char	last;

	quote = 0;
	dquote = 0;
	last = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\\')
			i++;
		else
			proceed_in_loop(str[i], &quote, &dquote, &last);
		i++;
	}
	return (utils_in_quotes_ret(quote, dquote, i, str));
}
