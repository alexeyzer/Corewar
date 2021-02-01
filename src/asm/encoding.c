#include "asm.h"

int find_position(t_operation **list, t_operation *temp, char *arg)
{
	t_operation *find;

	find = *list;
	while (find)
	{
		if (ft_strequ(find->label, arg))
			return (find->position - temp->position);
		find = find->next;
	}
	return (0);
}

void find_labels(t_operation **list)
{
	t_operation *temp;
	int i;
	int pos;

	temp = *list;
	while (temp)
	{
		i = 0;
		pos = 0;
		if (temp->op_name)
		{
			while (temp->arg[i] && i < 3)
			{
				if ((pos = ft_chrpos(temp->arg[i], LABEL_CHAR)) >= 0)
					temp->label_pos[i] = find_position(list, temp, \
                    temp->arg[i] + pos + 1);
				i = i + 1;
			}
		}
		temp = temp->next;
	}
}

char *continue_reading(int source_fd)
{
	char *line;
	char *ret;
	int flag;

	flag = 0;
	ret = ft_strnew(10);
	while (get_next_line(source_fd, &line) > 0)
	{
		if (ft_strchr(line, '\"'))
		{
			flag = 1;
			ret = strjoin_first(ret, "\n");
			ret = strjoin_first(ret, line);
			free(line);
			break;
		} else if (!ft_strchr(line, '\"'))
		{
			ret = strjoin_first(ret, "\n");
			ret = strjoin_first(ret, line);
		}
		free(line);
	}
	(!flag) ? err_manager(ERR_NAME, 1, NULL, NULL) : 0;
	return (ret);
}

char *save_name_comment(int source_fd, char *line)
{
	char *ret;
	int cnt;
	int pos_start;
	char *cntd;

	cnt = 0;
	while (line[cnt] != '\"')
		if (!line[cnt++])
			err_manager(ERR_NONAME, 1, NULL, NULL);
	pos_start = cnt++ + 1;
	while (line[cnt] != '\0' && line[cnt++] != '\"')
		continue;
	if (line[cnt] == '\0')
	{
		ret = ft_strdup(&line[pos_start]);
		cntd = continue_reading(source_fd);
		ret = strjoin_first(ret, cntd);
		free(cntd);
	} else
		ret = ft_strdup(&line[pos_start]);
	return (remove_trailing_spaces(ret));
}

void read_file(t_asm *core, int source_fd, t_operation **list)
{
	char *line;
	char *tmp;

	while (get_next_line(source_fd, &line) > 0)
	{
		tmp = line;
		core->line_cnt++;
		while (((*tmp == ' ' || *tmp == '\t') && *tmp != '\0') && tmp++)
			continue;
		if (ft_strnstr(tmp, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
		{
			if (core->champ_name)
				err_manager(ERR_MULTI_NAME, 1, NULL, NULL);
			core->champ_name = save_name_comment(source_fd, line);
		}
		else if (ft_strnstr(tmp, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)))
		{
			if (core->champ_comment)
				err_manager(ERR_MULTI_COMMEND, 1, NULL, NULL);
			core->champ_comment = save_name_comment(source_fd, line);
		}
		else
			lex_parser(core, list, line);
		free(line);
	}
	do_checks(core, list);
}
