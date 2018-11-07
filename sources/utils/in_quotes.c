/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 09:52:48 by tmaraval          #+#    #+#             */
/*   Updated: 2018/11/07 12:42:07 by tomux            ###   ########.fr       */
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
	int bslash_cnt;

	bslash_cnt = 0;
	if ((dquote == 0 && quote == 0) == 1)
	{
		if ((i = ft_strlen(str)) > 0)
		{
			if (str[i - 1] == '\\')
			{
				while (str[i - 1] == '\\')
				{
					i--;
					bslash_cnt++;
				}
				if (bslash_cnt % 2 != 0)
					return (0);
			}
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
