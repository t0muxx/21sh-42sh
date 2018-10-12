/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 12:01:30 by tmaraval          #+#    #+#             */
/*   Updated: 2018/10/11 12:03:33 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "env.h"

void	create_base_path(t_buffer *tbuffer)
{
	ft_bzero(tbuffer->base_path, 1024);
	getcwd(tbuffer->base_path, 1024);
	ft_strcat(tbuffer->base_path, "/.history");
}

void	increment_shlvl(char ***env)
{
	char	*shlvl;
	int		i_shlvl;

	i_shlvl = 0;
	if ((shlvl = env_get_var("SHLVL", *env)) == NULL)
		return ;
	i_shlvl = ft_atoi(shlvl);
	i_shlvl++;
	free(shlvl);
	shlvl = ft_itoa(i_shlvl);
	env_update_var("SHLVL", shlvl, *env);
	free(shlvl);
}
