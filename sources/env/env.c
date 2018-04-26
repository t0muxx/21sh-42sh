/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 14:16:58 by tmaraval          #+#    #+#             */
/*   Updated: 2018/04/25 11:32:00 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

int		env_until_equal(char *var)
{
	int i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	return (i);
}

char	*env_get_var(char *name, char **myenv)
{
	int			i;
	char		*temp;

	i = 0;
	if (name == NULL)
		return (NULL);
	while (myenv[i])
	{
		temp = ft_strsub(myenv[i], 0, env_until_equal(myenv[i]));
		if (ft_strcmp(temp, name) == 0 && ft_strlen(temp) == ft_strlen(name))
		{
			free(temp);
			temp = ft_strsub(myenv[i], ft_strlen(name) + 1,
			(ft_strlen(myenv[i]) - (ft_strlen(name) + 1)));
			if (ft_strlen(temp) == 0)
			{
				free(temp);
				return (NULL);
			}
			return (temp);
		}
		free(temp);
		i++;
	}
	return (NULL);
}

void	env_print(char **myenv)
{
	int		i;

	i = 0;
	while (myenv[i])
	{
		write(1, myenv[i], ft_strlen(myenv[i]));
		write(1, "\n", 1);
		i++;
	}
}

char	**env_create(void)
{
	char		**myenv;
	char		pwd[PATH_MAX];

	if (!(myenv = (char **)malloc(sizeof(char *) * 7)))
		error_malloc_err();
	myenv[0] = ft_strdup("PWD=");
	myenv[1] = ft_strdup("SHELL=");
	myenv[2] = ft_strdup("PATH=");
	myenv[3] = ft_strdup("HOME=");
	myenv[4] = ft_strdup("OLDPWD=");
	myenv[5] = ft_strdup("TERM");
	myenv[6] = 0;
	getcwd(pwd, PATH_MAX);
	env_update_var("PWD", pwd, myenv);
	env_update_var("SHELL", "minishell", myenv);
	env_update_var("TERM", "xterm-256color", myenv);
	return (myenv);
}

char	**env_create_copy(void)
{
	extern char **environ;
	char		**myenv;
	int			i;

	i = 0;
	while (environ[i])
		i++;
	if (i == 0)
		return (env_create());
	if (!((myenv = (char **)malloc(sizeof(char *) * (i + 1)))))
		error_malloc_err();
	i = 0;
	while (environ[i])
	{
		if (!(myenv[i] = (char *)malloc(sizeof(char) *
		ft_strlen(environ[i]) + 1)))
			error_malloc_err();
		ft_strcpy(myenv[i], environ[i]);
		i++;
	}
	myenv[i] = 0;
	return (myenv);
}
