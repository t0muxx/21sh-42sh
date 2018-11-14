/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomux </var/mail/tomux>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 16:40:56 by tomux             #+#    #+#             */
/*   Updated: 2018/11/14 11:38:03 by tomux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "env.h" 

/*
 * En gros on appelera la fonction tilde_exp_browse_tkn
 *  Apres le lexer.
 *  Elle explore les tkn et check si ya un tilde a expand.
 *  Si oui on fait de la jolie manipulation de string pour 
 *  expand et on change le tkn->type en WORD comme ca on est bien \0/
 *
 * t'as un ptit main de test en dessous decommente le et compile avec :
 * cd sources/lexer ; gcc tilde_expand.c -I../../includes ../../../libft/libft.a
 * 
 *
 * vois les tkn->data possible 
 *	pour un tkn->type TILDE
 *	sur lesquelles je me suis basé
 * "~"
 * "~/"
 * "~/suivi_dun_/_path"
 *
 * Comme tu peux le voir j'ai utiliser getenv() en attendant
 * qu'on ai tout implementé, j'aurai juste a rajouter ***env dans l'appel de 
 * mes fonctions, mais j'attends que t'es implementé le tkn tilde dans le 
 * lexer pour le faire :)
 *
 */

int		is_tilde_type(char *str)
{
	int		len;

	len = ft_strlen(str);
	if (len > 0 && str[0] == '~' )
	{
		if (len > 1 && str[1] != '/')
			return (0);
		else
			return (1);
	}
	return (0);
}

char 	*tilde_expand(char **str, char ***env)
{
	char *path;
	char *new;

	path = env_get_var("HOME", *env);
	//dprintf(2, "DEBUG : str |%s|\n", *str);
	new = ft_strjoin(path, *str + 1);
	//	free(path);
	free(*str);
	//dprintf(2, "DEBUG : new = |%s|\n", new);
	return (new);
}

void	tilde_exp_browse_tkn(t_tkn *tkn, char ***env)
{
	t_tkn *cpy;

	cpy = tkn;
	while (cpy != NULL)
	{
		if (cpy->type == CHR_TILDE)
		{
			cpy->data = tilde_expand(&cpy->data, env);
			cpy->type = CHR_WORD;
		}
		//dprintf(2, "DEBUG : cpy->data = |%s|\n", cpy->data);
		cpy = cpy->next;
	}
}
/*
   int 	main(void)
   {
   t_tkn *tkn1 = malloc(sizeof(t_tkn));
   t_tkn *tkn2 = malloc(sizeof(t_tkn));
   t_tkn *tkn3 = malloc(sizeof(t_tkn));
   t_tkn *tkn4 = malloc(sizeof(t_tkn));

   tkn1->data = strdup("ls ");
   tkn1->type = CHR_WORD;
   tkn1->next = tkn2;
   tkn2->data = ft_strdup("~ ");
   tkn2->type = CHR_TILDE;
   tkn2->next = tkn3;
   tkn3->data = ft_strdup("~/ ");
   tkn3->type = CHR_TILDE;
   tkn3->next = tkn4;
   tkn4->data = ft_strdup("~/test1 ");
   tkn4->type = CHR_TILDE;
   tkn4->next = NULL;

   printf("tkn1->data = |%s|\n", tkn1->data);
   printf("tkn2->data = |%s|\n", tkn2->data);
   printf("tkn3->data = |%s|\n", tkn3->data);
   printf("tkn4->data = |%s|\n", tkn4->data);
   tilde_exp_browse_tkn(tkn1);
   printf("tkn1->data = |%s|\n", tkn1->data);
   printf("tkn2->data = |%s|\n", tkn2->data);
   printf("tkn3->data = |%s|\n", tkn3->data);
   printf("tkn4->data = |%s|\n", tkn4->data);
   }
   */
