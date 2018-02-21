/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaraval <tmaraval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 16:38:11 by tmaraval          #+#    #+#             */
/*   Updated: 2018/02/02 13:44:15 by tmaraval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define UNDEFINEDERR 1
# define PERMERR	  2
# define EXISTERR	  3
# define HOMEERR	  4
# define TOMANYARG	  6
# define ALNUMERR	  7
# define TOOFEWARG	  8
# define EXECVERR	  9

void	error_malloc_err(void);
void	error_print(int errnbr, char *func, char *arg);
void	error_print_usage(char *usage);
void	error_fork_err(void);

#endif
