#include "ft_nm.h"
#include <stdio.h>


int		error_no_symbol(char *name_file)
{
	dprintf(2,"%s: %s: no symbols\n", NAME, name_file);
		return (ERROR);
}
