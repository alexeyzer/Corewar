//
// Created by Kudzu Psylocke on 1/31/21.
//

# ifndef ASM3_ERRORS_H
#define ASM3_ERRORS_H

#define ERR_MALLOC 1
void err_manager(size_t err, size_t is_exit, void *f, void *p);
void	*ft_protected_calloc(size_t len);


#define ERR_PARSE_COMMAND	(0)
#define ERR_PARSE_NONAME	(1)
#define ERR_PARSE_LEXICAL	(2)
#define ERR_NAME			(3)
#define ERR_NONAME			(4)
#define ERR_MULTI_NAME		(5)
#define ERR_MULTI_COMMEND	(6)


#endif
