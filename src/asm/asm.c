#include "asm.h"

int		main(int argc, char **argv)
{
	t_asm		*core;
	t_operation	*list;

	if (argc == 2)
	{
		core = intialize_asm(argv[1]);
		list = NULL;
		read_file(core, core->source_fd, &list);
		write_champion(core, list);
		free_list(list);
		clear_t_asm(core);
	}
	else
		ft_printf("./asm <filename.s>");
	return (0);
}

static short	ft_ulonglen(unsigned long n)
{
	size_t cnt;

	cnt = (n <= 0 ? 1 : 0);
	while (n != 0)
	{
		n = n / 10;
		cnt = cnt + 1;
	}
	return (cnt);
}

char			*ft_ultoa(unsigned long n)
{
	char	*res;
	size_t	len;
	size_t	i;

	len = ft_ulonglen(n);
	if (!(res = ft_strnew(len)))
		return (NULL);
	i = 0;
	if (n == 0)
		res[i] = '0';
	while (n != 0)
	{
		res[len - 1] = (n % 10) + 48;
		n = n / 10;
		len = len - 1;
	}
	return (res);
}


int		ft_strendwith(const char *src, const char *suffix)
{
	size_t src_l;
	size_t suf_l;

	src_l = ft_strlen(src);
	suf_l = ft_strlen(suffix);
	return (suf_l <= src_l && ft_strequ(src + src_l - suf_l, suffix));
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\r' || c == '\n' || \
		c == '\f' || c == '\v' || c == '\t')
		return (1);
	return (0);
}

