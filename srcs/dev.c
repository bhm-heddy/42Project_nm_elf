#include <stdio.h>
#include "ft_nm.h"

void	print_sh_type(uint32_t i)
{
	if (i == SHT_NULL)
		printf("type = [SHT_NULL]");
	else if (i == SHT_PROGBITS)
		printf("type = [SHT_PROGBITS]");
	else if (i == SHT_SYMTAB)
		printf("type = [SHT_SYMTAB]");
	else if (i == SHT_STRTAB)
		printf("type = [SHT_STRTAB]");
	else if (i == SHT_RELA)
		printf("type = [SHT_RELA]");
	else if (i == SHT_HASH)
		printf("type = [SHT_HASH]");
	else if (i == SHT_DYNAMIC)
		printf("type = [SHT_DYNAMIC]");
	else if (i == SHT_NOTE)
		printf("type = [SHT_NOTE]");
	else if (i == SHT_NOBITS)
		printf("type = [SHT_NOTBITS]");
	else if (i == SHT_REL)
		printf("type = [SHT_REL]");
	else if (i == SHT_SHLIB)
		printf("type = [SHT_SHLIB]");
	else if (i == SHT_DYNSYM)
		printf("type = [SHT_DYNSYM]");
	else if (i == SHT_LOPROC)
		printf("type = [SHT_LOPROC SHT_HIPROC]");
	else if (i == SHT_LOUSER)
		printf("type = [SHT_LOUSER]");
	else if (i == SHT_HIUSER)
		printf("type = [SHT_HIUSER]");
	else
		printf("type = [%d]", i);
}

void	print_section(t_elfH *e)
{
	int i = 0;

	printf("[E_SHNUM] = %d sections\n", e->ehdr->e_shnum);
	while (i < e->ehdr->e_shnum)
	{
		if (e->shdr[i].sh_type == SHT_SYMTAB)
			printf("---->>");
		printf("\t[%d]| ", i);
		print_sh_type(e->shdr[i].sh_type);
		printf("-> [%s] | FLAG", e->strtable + e->shdr[i].sh_name);
		printf(" [%lu]\n", e->shdr[i].sh_flags);
		i++;
	}
}



uint8_t	is_xbit(t_elfH *elf)
{
	if (((char *)elf->file)[EI_CLASS] == ELFCLASS32)
		return ((elf->xbit = 32));
	else
		return ((elf->xbit = 64));
}
