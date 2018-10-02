//insert header


#ifndef GLOBAL_H
# define GLOBAL_H
# define GLOBAL_BUF 128

#include "exec.h"

typedef struct	s_global {
	char	*key;
	char	*value;
}		t_global;

extern struct s_global	globals[128];

void	insert_global(char *str, char ***env);
void	remove_global(char *str);
char	*get_global_key(char *value);
char	*get_global_value(char *key, char **env);

#endif
