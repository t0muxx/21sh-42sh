/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_trim.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 10:36:17 by tmaraval          #+#    #+#             */
/*   Updated: 2018/09/05 13:26:01 by tmaraval         ###   ########.fr       */

/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"
#include "unistd.h"

void	completion_trim_get_searchdir_fill_ret(char *userinput, char **ret)
{
	int last_slash;

	last_slash = 0;
//	printf("userinput = |%s|\n", userinput);
	last_slash = make_path_find_last_slash(userinput);
//	printf("last slash |%d|\n", last_slash);
	ret[0] = malloc(sizeof(char) * (last_slash + 2));
	ft_strncpy(ret[0], userinput, (size_t)(last_slash + 1));
//	printf("|%s|\n", ret[0]);
	ret[0][last_slash + 2] = '\0';
	
}

char	*completion_trim_get_searchdir(char *userinput)
{
	char *ret;
	
	if (userinput == NULL || ft_strlen(userinput) == 0)
		ret = ft_strdup(".");
	else if (userinput[0] == '/' || !ft_strncmp(userinput, "./", 2) || !ft_strncmp(userinput, "../", 3))
		completion_trim_get_searchdir_fill_ret(userinput, &ret);
	else
	{
		if (!ft_strchr(userinput, '/'))
			ret = ft_strdup(".");
		else
			completion_trim_get_searchdir_fill_ret(userinput, &ret);
	}
	return (ret);
}

char	*completion_trim_get_str_to_complete(char *userinput)
{
	int last_slash;
	char *ret;
	
	last_slash = make_path_find_last_slash(userinput);
	if (last_slash < ft_strlen(userinput))
		ret = ft_strsub(userinput, last_slash + 1, ft_strlen(userinput));
	else
		ret = ft_strdup("");
	return (ret);
}

/*int		main(int argc, char **argv)
{
	char *ret;
	char *ret2;

	ret = completion_trim_get_searchdir(argv[1]);
	ret2 = completion_trim_get_str_to_complete(argv[1]);
	printf("The corresponding searchdir : |%s|\n", ret);
	printf("The corresponding str to complete : |%s|\n", ret2);
}*/
