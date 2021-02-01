#include "asm.h"


static char 	check_extension(char *str)
{
	size_t		len;

	len = ft_strlen(str);
	if (len > 2 && str[len] == 's' && str[len - 1] == '.')
		return (1);
	return (0);
}



t_asm			*intialize_asm(char *filename)
{
	t_asm	*core;

	core = (t_asm *)ft_memalloc(sizeof(t_asm));
	if (!core)
		ft_printf("Malloc at initialize_asm");
	core->target_file = filename_pars(filename, SRC_TYPE, TRGT_TYPE);
	if (!core->target_file || check_extension(core->target_file))
	{
		ft_printf("Incorrect file type", core, clear_t_asm);
		exit(0);
	}

	core->source_fd = open(filename, O_RDONLY);
	if (core->source_fd < 0)
	{
		ft_printf("Open Error on source file", core, clear_t_asm);
		exit(0);
	}
	return (core);
}

t_operation		*newnode(void)
{
	t_operation *new;

	new = (t_operation*)ft_memalloc(sizeof(t_operation));
	return (new);
}

int				list_append(t_operation **head)
{
	t_operation *last;

	last = *head;
	if (*head == NULL)
	{
		*head = newnode();
		return (1);
	}
	while (last->next != NULL)
		last = last->next;
	last->next = newnode();
	return (1);
}
