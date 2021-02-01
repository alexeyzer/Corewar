#include "asm.h"

void					clear_t_asm(t_asm *object)
{
	if (object->source_fd > 2 && close(( object)->source_fd) < 0)
			ft_printf("Failed to close source file");
	if (object->core_fd > 2 && close(( object)->core_fd) < 0)
			ft_printf("Failed to close target file");
	(object->champ_name) ? free(( object)->champ_name) : 0;
	(object->champ_comment) ?  free(object->champ_comment): 0;
	(object->target_file) ? free(object->target_file): 0;
	free(object);
	exit(0);
}

void free_list(t_operation *list)
{
	t_operation *current_list;
	t_operation *temp_list;

	current_list = list;
	while (current_list)
	{
		(current_list->label) ? free(current_list->label) : 0;
		(current_list->op_name) ? free(current_list->op_name) : 0;
		(current_list->arg[0]) ? free(current_list->arg[0]) : 0;
		(current_list->arg[1]) ? free(current_list->arg[1]) : 0;
		(current_list->arg[2]) ? free(current_list->arg[2]) : 0;
		temp_list = current_list;
		current_list = current_list->next;
		free(temp_list);
	}
}
