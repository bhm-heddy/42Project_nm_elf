#include "ft_nm.h"

t_symbol	*find_symlink32(t_elfH *elf, t_elf32 *e32)
{
	int			sym_num;
	char		*sym_strtable;
	t_symbol	sym;
	t_symbol	*lst = NULL;

	sym_num = e32->shdr[elf->sh_index].sh_size / e32->shdr[elf->sh_index].sh_entsize;
	sym_strtable = elf->file + e32->shdr[e32->shdr[elf->sh_index].sh_link].sh_offset;
	 for (int i = 0; i < sym_num; i++)
	 {
		 if (e32->sym[i].st_name != 0
			&& ELF32_ST_TYPE(e32->sym[i].st_info) != STT_FILE
			&& ELF32_ST_TYPE(e32->sym[i].st_info) != STT_SECTION)
		 {
			sym.type = ELF32_ST_TYPE(e32->sym[i].st_info);
			sym.bind = ELF32_ST_BIND(e32->sym[i].st_info);
			sym.name = sym_strtable + e32->sym[i].st_name;
			sym.shndx = e32->sym[i].st_shndx;
			sym.value = e32->sym[i].st_value;
			create_lst_symbol(&lst, &sym);
		 }
	 }
	 return (lst);
}

int32_t		find_symtab32(char *file, t_elf32 *e)
{
	for (uint16_t i = 0; i < e->ehdr->e_shnum; i++)
	{
		if (e->shdr[i].sh_type == SHT_SYMTAB)
		{
			e->sym = (Elf32_Sym *)(file + e->shdr[i].sh_offset);
			return (i);
		}
	}
	return (ERROR);// -1 
	/*
	 *ajout section dynsym pour option -D
	 */
}
