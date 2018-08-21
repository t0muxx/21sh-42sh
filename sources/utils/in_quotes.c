/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomux </var/mail/tomux>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 13:43:25 by tomux             #+#    #+#             */
/*   Updated: 2018/08/20 14:28:11 by tomux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline.h>

int	utils_in_quotes(char *str)
{
	int i;
	int quote;
	int dquote;
	char last;

	quote = 0;
	dquote = 0;
	last = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"' && dquote == 0 && quote == 0)
		{
			dquote = 1;
			last = '"';
		}
		else if (str[i] == '"' && dquote == 1 && last == '"')
		{
			dquote = 0;
			last = 0;
		}
		if (str[i] == '\'' && quote == 0 && dquote == 0)
		{
			quote = 1;
			last = '\'';
		}
		else if (str[i] == '\'' && quote == 1 && last == '\'')
		{
			quote = 0;
			last = 0;
		}
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
