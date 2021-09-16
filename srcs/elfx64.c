#include "ft_nm.h"

t_symbol	*find_symlink64(t_elfH *elf, t_elf64 *e64)
{
	int			sym_num;
	char		*sym_strtable;
	t_symbol	sym;
	t_symbol	*lst = NULL;

	sym_num = e64->shdr[elf->sh_index].sh_size / e64->shdr[elf->sh_index].sh_entsize;
	sym_strtable = elf->file + e64->shdr[e64->shdr[elf->sh_index].sh_link].sh_offset;
	 for (int i = 0; i < sym_num; i++)
	 {
		 if (e64->sym[i].st_name != 0
			&& ELF64_ST_TYPE(e64->sym[i].st_info) != STT_FILE
			&& ELF64_ST_TYPE(e64->sym[i].st_info) != STT_SECTION)
		 {
			sym.type = ELF64_ST_TYPE(e64->sym[i].st_info);
			sym.bind = ELF64_ST_BIND(e64->sym[i].st_info);
			sym.name = sym_strtable + e64->sym[i].st_name;
			sym.shndx = e64->sym[i].st_shndx;
			sym.value = e64->sym[i].st_value;
			if (create_lst_symbol(&lst, &sym) != SUCCESS)
				return (NULL);
		 }
	 }
	 return (lst);
}

int32_t		find_symtab64(char *file, t_elf64 *e)
{
	for (uint16_t i = 0; i < e->ehdr->e_shnum; i++)
	{
		if (e->shdr[i].sh_type == SHT_SYMTAB)
		{
			e->sym = (Elf64_Sym *)(file + e->shdr[i].sh_offset);
			return (i);
		}
	}
	return (ERROR);
}
