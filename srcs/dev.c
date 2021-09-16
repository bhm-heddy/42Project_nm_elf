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

void	debug_print_type(Elf64_Half type)
{
	printf("type value = [%d] ", type);
	if (type == ET_NONE)
		printf("type = [ET_NONE]\n");
	else if (type == ET_CORE)
		printf("type = [ET_CORE]\n");
	else if (type == ET_NUM)
		printf("type = [ET_NUM]\n");
	else if (type == ET_LOOS )
		printf("type = [ET_LOOS]\n");
	else if (type == ET_HIOS)
		printf("type = [ET_HIOS]\n");
	else if (type == ET_LOPROC )
		printf("type = [ET_LOPROC]\n");
	else if (type == ET_HIPROC)
		printf("type = [ET_HIPROC]\n");
	else
		printf("dont understand type\n");
}




//	if (strcmp(sym->name, ".str") == 0)
//		debug(&e->e64, sym);
//		debug2(&e->e64, sym);

 /*void	debug2(t_elf64 *e, t_symbol *sym)
 *{
 *    if (sym->type == 1 && e->shdr[sym->shndx].sh_type == 1 && e->shdr[sym->shndx].sh_flags == 2)
 *    {
 *        printf("----------------------------\n");
 *        printf("\t 1312 [%s]\n", sym->name);
 *        printf("----------------------------\n");
 *    }
 *}
 */


//	if (strcmp(sym->name, "__bss_start") == 0)
//		debug(&e->e64, sym);

 void	debug(t_elf64 *e, t_symbol *sym)
 {
	 printf("[%s] \n", sym->name);
	 printf("type  = [%d]\nsh-type = [%d]\n sh_flags = [%lu]\n", sym->type,
			 e->shdr[sym->shndx].sh_type, e->shdr[sym->shndx].sh_flags);
	 exit(1);
 }
