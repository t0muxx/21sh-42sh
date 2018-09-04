/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 09:52:48 by tmaraval          #+#    #+#             */
/*   Updated: 2018/09/04 09:57:17 by tmaraval         ###   ########.fr       */
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
		proceed_in_loop(str[i], &quote, &dquote, &last);
		i++;
	}
	return (dquote == 0 && quote == 0);
}

/*int	main(int argc, char **argv)
{
	char **test;
	int i;

	i = 0;
	test = (char **)malloc(sizeof(char *) * 10);

	test[0] = strdup("\"12345678\"");
	test[1] = strdup("\"1234'5'8\"");
	test[2] = strdup("\"1\"2\"567\"");
	test[3] = strdup("'123\"4\"78'");
	test[4] = strdup("'123\"4\"78'\"");
	test[5] = strdup("'123\"4'\"78'");
	test[6] = strdup("'1'\"2\"3\"4\"7'8'\"");
	test[7] = strdup("'1\"23'4\"7\"8");
	test[8] = strdup("'12\"3\"4\"7'\"8");
	test[9] = strdup("'\"123\"4\"7'\"8'");
	while (i < 10)
	{
		puts("testing :");
		puts(test[i]);
		puts("\n");
		if (utils_in_quotes(test[i]) == 1)
			puts("OK\n");
		else
			puts("KO\n");
		i++;
	}
	return (0);
}*/
