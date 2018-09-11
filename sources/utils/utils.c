/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlulu <tomlulu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 18:02:52 by tomlulu           #+#    #+#             */
/*   Updated: 2018/09/11 15:41:09 by tomux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "unistd.h"
#include <sys/stat.h>

int	utils_is_dir(char *path)
{
	struct stat buf;

	if (stat(path, &buf) != -1)
	{
		if (S_ISDIR(buf.st_mode))
			return (1);
	}
	return (0);
}
