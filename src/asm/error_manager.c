#include "asm.h"


void *ft_protected_calloc(size_t len)
{
	void *p;

	if (len <= 0)
		return (NULL);
	p = ft_memalloc(len);
	if (!p)
	{
		ft_printf("Malloc error");
		exit(0);
	}

	return (p);
}


void err_manager(size_t err, size_t is_exit, void *p, void *f)
{

	(err == ERR_PARSE_COMMAND) ? ft_printf("Invalid command on line %d\n", *(int *)p) : 0;
	(err == ERR_PARSE_NONAME) ? ft_printf("Name or comment missing\n") : 0;
	(err == ERR_PARSE_LEXICAL) ? ft_printf("Lexical error!\n") : 0;
	(err == ERR_NAME) ? ft_printf("Incorrect name/comment\n") : 0;
	(err == ERR_NONAME) ? ft_printf("No name or comment!\n") : 0;
	(err == ERR_MULTI_NAME) ? ft_printf("Multiple names!\n") : 0;
	(err == ERR_MULTI_COMMEND) ? ft_printf("Multiple comments!\n") : 0;


	(p != NULL) ? free(f) : 0;
	(is_exit) ? exit(0) : 0;
	exit(0);
}
