/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 08:55:11 by tmaraval          #+#    #+#             */
/*   Updated: 2018/04/23 08:57:23 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H 

char	**env_create_copy(void);
char	**env_create(void);
void	env_print(char **myenv);
char	*env_get_var(char *name, char **myenv);
int		env_until_equal(char *var);
int		env_delete_var(char *name, char ***myenv);
char	**env_add_var(char *name, char *value, char **myenv);
int		env_update_var(char *name, char *value, char **myenv);

#endif
