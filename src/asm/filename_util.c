#include "asm.h"


char	*filename_pars(const char *source, const char *src_type,\
		const char *target_type)
{
	char	*target;
	char	*base;

	target = NULL;
	if (ft_strendwith(source, src_type))
	{
		base = ft_strsub(source, 0, ft_strlen(source) - ft_strlen(src_type));
		target = ft_strjoin(base, target_type);
		free(base);
	}
	return (target);
}
