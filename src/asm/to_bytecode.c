#include "asm.h"

void	write_champion(t_asm *core, t_operation *op)
{
	core->core_fd = open(core->target_file, O_RDWR | O_TRUNC | O_CREAT, 0600);
	if (core->core_fd < 0)
		ft_printf("Open Error on target file", core, clear_t_asm);
	write_headers(core);
	write_exec_code(core, op);
	ft_printf("Writing output program to: %s\n", core->target_file);
}
