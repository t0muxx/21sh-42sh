/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_cmp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 15:22:37 by tmaraval          #+#    #+#             */
/*   Updated: 2018/09/04 15:47:55 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char **completion_cmp_userinput_filelist(char *userinput, char **filelist)
{
	char **ret;
	int  i;
	int j;

	i = 0;
	while (filelist[i])
	{
		j = 0;
		while (filelist[i][j] == userinput[j] && filelist[i][j] && userinput[i][j])
			j++;
		if (j > 0)
		{

		}
		i++;
	}
	return (ret);
}
