#include "asm.h"

void		get_hex(t_operation *new, char *line, int cnt)
{
	char	*temp;
	char	*hex;

	temp = x_to_deci(line);
	hex = ft_strjoin("%", temp);
	new->arg[cnt] = ft_strdup(hex);
	free(temp);
	free(hex);
}

void		label_error(t_operation *finder, int cnt)
{
	ft_printf("Invalid argument: \"%s\" on line %d\n", \
				finder->arg[cnt], finder->line);
	ft_printf("Argument error!");
}
