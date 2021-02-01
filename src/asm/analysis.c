#include "asm.h"

void	skip_space(char *line, char *reform, int *i, int *pos)
{
	reform[*pos] = ' ';
	*pos += 1;
	while (line[*i] == ' ' || line[*i] == '\t')
		*i += 1;
	*i -= 1;
}

char	*reduce_whitespace(char *line, char *reform, int *i, int *pos)
{
	while (line[*i])
	{
		if (line[*i] == COMMENT_CHAR || line[*i] == ALT_COMMENT_CHAR)
		{
			line[*i] = '\0';
			break ;
		}
		if (line[*i] != ' ' && line[*i] != '\t')
		{
			if ((line[*i] == DIRECT_CHAR || line[*i] == '-') && \
				line[*i - 1] != ' ' && line[*i - 1] != '\t' && \
				line[*i - 1] != SEPARATOR_CHAR)
			{
				reform[*pos] = ' ';
				*pos += 1;
			}
			reform[*pos] = line[*i];
			*pos += 1;
		}
		else
			skip_space(line, reform, i, pos);
		*i += 1;
	}
	(reform[*pos - 1] == ' ') ? *pos -= 1 : 0;
	return (reform);
}

char	*final_reformat(char *reform, int *i, int *pos, int separator)
{
	char	*final;


	if (!(final = (char*)malloc(sizeof(char) * ft_strlen(reform) + 2)))
		ft_printf("Malloc error");
	while (reform[*pos])
	{
		if (reform[*pos] != ' ')
		{
			final[*i] = reform[*pos];
			*i += 1;
		}
		else if (reform[*pos] == ' ' && !separator)
		{
			(reform[*pos - 1] == LABEL_CHAR) ? (final[*i] = SEPARATOR_CHAR) : 0;
			if (ft_isalpha(reform[*pos - 1]) && !separator)
			{
				final[*i] = SEPARATOR_CHAR;
				separator = 1;
			}
			*i += 1;
		}
		*pos += 1;
	}
	ft_strdel(&reform);
	return (final);
}

char	*reformat(char *line)
{
	int		i;
	int		pos;
	char	*reform;

	i = 0;
	pos = 0;
	reform = (char*)ft_protected_calloc(sizeof(char) * ft_strlen(line) + 2);
	reform = reduce_whitespace(line, reform, &i, &pos);
	reform[pos] = '\0';
	pos = 0;
	i = 0;
	reform = final_reformat(reform, &i, &pos, 0);
	reform[i] = SEPARATOR_CHAR;
	reform[i + 1] = '\0';
	return (reform);
}

void	lex_parser(t_asm *core, t_operation **list, char *line)
{
	char	*reform;

	if (!line || line[0] == '\0')
		return ;
	while (*line == ' ' || *line == '\t')
		line = line + 1;
	if (*line == '\0')
		return ;
	else if (*line == COMMENT_CHAR || *line == ALT_COMMENT_CHAR)
		return ;
	else if (!core->champ_name || !core->champ_comment || *line == '.')
	{
		if (*line == '.')
			err_manager(ERR_PARSE_COMMAND, 0, &core->line_cnt, NULL);
		else
			err_manager(ERR_PARSE_NONAME, 0, 0, NULL);
		err_manager(ERR_PARSE_LEXICAL, 1, 0, NULL);
	}
	reform = reformat(line);
	list_append(list);
	get_label_op(core, list, reform);
	free(reform);
}
