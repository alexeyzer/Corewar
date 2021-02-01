#include "asm.h"

void		get_args(t_operation *new, char *line)
{
	int		i;
	int		cnt;

	i = 0;
	cnt = 0;
	while (line[i])
	{
		if (line[i] == SEPARATOR_CHAR)
		{
			if (cnt > 2)
			{
				ft_printf("Too many arguments on line %d\n", new->line);
				ft_printf("Argument error!");
				exit(0);
			}
			line[i] = '\0';
			if (is_hex(line))
				get_hex(new, line, cnt);
			else
				new->arg[cnt] = ft_strdup(line);
			line = line + i + 1;
			cnt += 1;
			i = -1;
		}
		i += 1;
	}
}

void		check_dup_labels(t_operation **list, char *label, int line)
{
	t_operation *temp;

	temp = *list;
	while (temp->next)
	{
		if (ft_strequ(temp->label, label))
		{
			ft_printf("Invalid label: \"%s\" on line %d\n", label, line);
			ft_printf("Duplicate label!");
		}
		temp = temp->next;
	}
}

static void	save_label(t_operation **list, t_operation *new, char *line)
{
	int pos;

	if (new->label != NULL)
	{
		pos = new->line;
		list_append(list);
		new = new->next;
		new->line = pos;
	}
	new->label = ft_strdup(line);
	check_label_chars(new->label, new->line);
	check_dup_labels(list, new->label, new->line);
}

int			save_label_op(t_operation **list, t_operation *new, \
			char *line, int *i)
{
	char	*tmp;

	if (line[*i] == SEPARATOR_CHAR && line[*i - 1] == LABEL_CHAR)
	{
		line[*i - 1] = '\0';
		save_label(list, new, line);
	}
	else if (line[*i] == SEPARATOR_CHAR && line[*i - 1] != LABEL_CHAR)
	{
		line[*i] = '\0';
		tmp = ft_strchr(line, LABEL_CHAR);
		if (tmp)
		{
			tmp[0] = '\0';
			tmp++;
			save_label(list, new, line);
			new->op_name = ft_strdup(tmp);
		}
		else
			new->op_name = ft_strdup(line);
		return (0);
	}
	return (1);
}

void		get_label_op(t_asm *core, t_operation **list, char *line)
{
	int			i;
	t_operation	*new;

	i = 0;
	new = *list;
	while (new->next)
		new = new->next;
	new->line = core->line_cnt;
	while (line[i])
	{
		if (line[i] == SEPARATOR_CHAR)
		{
			save_label_op(list, new, line, &i);
			line = line + i + 1;
			i = 0;
			if (new->op_name)
				break ;
		}
		(line[i] != '\0') ? (i += 1) : 0;
	}
	if (new->op_name)
	{
		get_args(new, line);
		check_operation(new, core);
	}
}
