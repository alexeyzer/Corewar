#include "asm.h"

void	check_further(t_operation *operation, t_oplist ref, t_asm *core)
{
	int	cnt;
	int	ret;

	cnt = 0;
	while (cnt < ref.arg_cnt)
	{
		ret = check_argument(operation->arg[cnt], core);
		if ((ret | ref.arg_type[cnt]) == ref.arg_type[cnt] && ret != 0)
			operation->argtypes[cnt] = ret;
		else
		{
			ft_printf("Invalid argument: \"%s\" on line %d\n", \
						operation->arg[cnt], core->line_cnt);
			ft_printf("Wrong argument type!");
		}
		cnt += 1;
	}
	if (cnt < 3 && operation->arg[cnt])
	{
		ft_printf("Invalid arguments on line: %d\n", core->line_cnt);
		ft_printf("Wrong argument number!");
	}
	operation->arg_type_code = ref.arg_type_code;
	operation->op_code = ref.opcode;
}

void	check_operation(t_operation *operation, t_asm *core)
{
	int cnt;

	cnt = 0;
	while (cnt < 16)
	{
		if (ft_strequ(operation->op_name, g_oplist[cnt].opname))
		{
			check_further(operation, g_oplist[cnt], core);
			break ;
		}
		cnt += 1;
	}
	if (cnt == 16)
	{
		ft_printf("Invalid instruction: \"%s\" on line %d\n", \
					operation->op_name, core->line_cnt);
		ft_printf("No operation found!");
	}
}
