/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_trim.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 11:28:31 by tmaraval          #+#    #+#             */
/*   Updated: 2018/09/11 15:42:16 by tomux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"
#include "unistd.h"
#include <sys/stat.h>

void	completion_trim_append_slash_do(char **newcontent, t_list *filelist)
{
	newcontent[0] = ft_memalloc(
	ft_strlen((char *)filelist->content) + 3);
	ft_strcat(newcontent[0], filelist->content);
	ft_strcat(newcontent[0], "/");
	newcontent[0][ft_strlen(newcontent[0]) + 1] = 0;
	free(filelist->content);
	filelist->content = newcontent[0];
}

void	completion_trim_append_slash(t_list *filelist, char **searchdir)
{
	struct stat		buf;
	char			*file;
	char			*newcontent;
	char			currentwdir[PATH_MAX];

	if (!ft_strcmp(searchdir[0], "."))
	{
		free(searchdir[0]);
		getcwd(currentwdir, PATH_MAX);
		searchdir[0] = ft_strdup(currentwdir);
	}
	if (!(searchdir[0][0] == '/' && ft_strlen(searchdir[0]) == 1))
		make_path_manage_last_slash(searchdir, PATH_REM_SLASH);
	while (filelist)
	{
		file = make_path(searchdir[0], filelist->content);
		if (utils_is_dir(file) == 1)
				completion_trim_append_slash_do(&newcontent, filelist);
		free(file);
		filelist = filelist->next;
	}
}

void	completion_trim_get_searchdir_fill_ret(char *userinput, char **ret)
{
	int last_slash;

	last_slash = 0;
	last_slash = make_path_find_last_slash(userinput);
	ret[0] = malloc(sizeof(char) * (last_slash + 2));
	ft_bzero(ret[0], last_slash + 2);
	ft_strncpy(ret[0], userinput, (size_t)(last_slash + 1));
}

char	*completion_trim_get_searchdir(char *userinput)
{
	char *ret;

	if (userinput == NULL || ft_strlen(userinput) == 0)
		ret = ft_strdup(".");
	else if (userinput[0] == '/' ||
	!ft_strncmp(userinput, "./", 2) || !ft_strncmp(userinput, "../", 3))
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
	int		last_slash;
	char	*ret;

	last_slash = make_path_find_last_slash(userinput);
	if (last_slash == 0 && userinput[0] != '/')
		ret = ft_strsub(userinput, last_slash, ft_strlen(userinput));
	else if (last_slash < (int)ft_strlen(userinput))
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
