// include header

#include "global.h"
#include "lexer.h"
#include "exec.h"


static char	*extract_assignment(char *str, int value)
{
	char	*dest;
	int	len;

	len = 0;
	if (value)
	{
		while (str[len] != '=' && str[len] != '\0')
			len++;
		str += ++len;
		len = ft_strlen(str);
	}
	else
	{
		while (str[len] != '=' && str[len] != '\0')
			len++;
	}

	if (!(dest = (char*)malloc(sizeof(char) * (len))))
		return (NULL);
	ft_strncpy(dest, str, len);
	return (dest);


}

char	*get_global_value(char *key)
{
	int	i;

	i = 0;
	while (globals[i].key != NULL)
	{
		if (ft_strcmp(globals[i].key, key) == 0)
			return (globals[i].value);
		i++;
	}
	return ("");
}

char	*get_global_key(char *value)
{
	int	i;
	
	i = 0;
	while (globals[i].value != NULL)
	{
		if (ft_strcmp(globals[i].value, value) == 0)
		{
			return (globals[i].key);
		}
	}
	return (NULL);
}

void		insert_global(char *str)
{
	int		i;
	t_global	new;

	i = 0;
	new.key = extract_assignment(str, 0);
	new.value = extract_assignment(str, 1);
	while (globals[i].key != NULL)
	{
		if (i >= GLOBAL_BUF)
			ft_putendl("max buf size reached");
			//func to realloc more on global array, and copy all globals in the new array)
		if (ft_strcmp(new.key, globals[i].key) == 0)
		{
			free(globals[i].key);
			free(globals[i].value);
			globals[i] = new;
			break ;
		}
		i++;
	}
	globals[i] = new;
}
