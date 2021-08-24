#include "ft_nm.h"
#include <stdio.h>

int		check_offset(void *ptr, void *end)
{
	if (ptr > end)
		return (ERROR);
	return (SUCCESS);
}

int		error_file_format(char *name_file)
{
		fprintf(stderr, "%s: %s: File format not recognized\n", NAME, name_file);
		return (ERROR);
}

int		error_corrupted_file(char *name_file)
{
	dprintf(2,"%s: %s: Corrupted file\n", NAME, name_file);
	g_my_errno = 1;
	return (ERROR);
}


int		error_endian_file(char *name_file)
{
	dprintf(2,"%s: %s: Different endian is not supported\n", NAME, name_file);
	g_my_errno = 1;
	return (ERROR);
}



int		error_no_symbol(char *name_file)
{
	dprintf(2,"%s: %s: no symbols\n", NAME, name_file);
	g_my_errno = 0;
		return (ERROR);
}
