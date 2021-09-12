#include "ft_nm.h"

static t_flags		localflags[] = {
  { STT_NOTYPE, SHT_PROGBITS, 0, 'n' },
  { STT_NOTYPE, SHT_INIT_ARRAY, 3, 'd' },
  { STT_NOTYPE, SHT_PROGBITS, 2, 'r' },
  { STT_NOTYPE, SHT_PROGBITS, 50, 'r' },
  { STT_NOTYPE, SHT_PROGBITS, 3, 'd' },
  { STT_NOTYPE, SHT_PROGBITS, 6, 't' },
  { STT_NOTYPE, SHT_NOBITS, 3, 'b' },
  { STT_OBJECT, SHT_DYNAMIC, 3, 'd' },
  { STT_OBJECT, SHT_NOTE, 2, 'r' },
  { STT_OBJECT, SHT_FINI_ARRAY, 3, 't' },
  { STT_OBJECT, SHT_INIT_ARRAY, 3, 't' },
  { STT_OBJECT, SHT_PROGBITS, 0, 'n' },
  { STT_OBJECT, SHT_PROGBITS, 2, 'r' },
  { STT_OBJECT, SHT_PROGBITS, 50, 'r' },
  { STT_OBJECT, SHT_PROGBITS, 3, 'd' },
  { STT_OBJECT, SHT_NOBITS, 3, 'b' },
  { STT_FUNC, SHT_PROGBITS, 6, 't' },
  { STT_TLS, SHT_PROGBITS, 1027, 'd' },
  { STT_TLS, SHT_NOBITS, 1027, 'b' },
  { STT_LOOS, SHT_PROGBITS, 6, 'i' }
};

static t_flags		globalflags[] = {
  { STT_NOTYPE, SHT_NULL, 0, 'U' },
  { STT_NOTYPE, SHT_PROGBITS, 3, 'D' },
  { STT_NOTYPE, SHT_PROGBITS, 6, 'T' },
  { STT_NOTYPE, SHT_NOBITS, 3, 'B' },
  { STT_OBJECT, SHT_NULL, 0, 'U' },
  { STT_OBJECT, SHT_PROGBITS, 3, 'D' },
  { STT_OBJECT, SHT_PROGBITS, 2, 'R' },
  { STT_OBJECT, SHT_PROGBITS, 18, 'R' },
  { STT_OBJECT, SHT_NOBITS, 3, 'B' },
  { STT_FUNC, SHT_NULL, 0, 'U' },
  { STT_FUNC, SHT_PROGBITS, 6, 'T' },
  { STT_TLS, SHT_NOBITS, 1027, 'B' },
  { STT_LOOS, SHT_PROGBITS, 6, 'i' }
};


char	c_flag(t_symbol *sym)
{
	if (sym->type == STT_OBJECT &&
			sym->shndx == SHN_COMMON)
		return ('C');
	return (NO_TYPE);
}

char	global_flag32(t_elfH *e, t_symbol *sym)
{
    Elf32_Shdr *sh = e->e32.shdr;

	for (int i = 0; i < GF_SIZE; i++)
	{
		if (sym->type == globalflags[i].stt)
			if(sh[sym->shndx].sh_type == globalflags[i].sh_type)
				if(sh[sym->shndx].sh_flags == globalflags[i].sh_flags)
					return (globalflags[i].type);
	}
	return ('?');
}

char	local_flag32(t_elfH *e, t_symbol *sym)
{
    Elf32_Shdr *sh = e->e32.shdr;

	for (int i = 0; i < LF_SIZE; i++)
	{
		if (sym->type == localflags[i].stt)
			if(sh[sym->shndx].sh_type == localflags[i].sh_type)
				if(sh[sym->shndx].sh_flags == localflags[i].sh_flags)
					return (localflags[i].type);
	}
	return ('?');
}

char	global_flag64(t_elfH *e, t_symbol *sym)
{
    Elf64_Shdr *sh = e->e64.shdr;

	for (int i = 0; i < GF_SIZE; i++)
	{
		if (sym->type == globalflags[i].stt)
			if(sh[sym->shndx].sh_type == globalflags[i].sh_type)
				if(sh[sym->shndx].sh_flags == globalflags[i].sh_flags)
				{
					return (globalflags[i].type);
				}
	}
	return ('?');
}

char	local_flag64(t_elfH *e, t_symbol *sym)
{
    Elf64_Shdr *sh = e->e64.shdr;

	for (int i = 0; i < LF_SIZE; i++)
	{
		if (sym->type == localflags[i].stt)
			if(sh[sym->shndx].sh_type == localflags[i].sh_type)
				if(sh[sym->shndx].sh_flags == localflags[i].sh_flags)
					return (localflags[i].type);
	}
	return ('?');
}

char	weak_flag64(t_symbol *sym)
{
	if (sym->type == STT_OBJECT)
		return (sym->shndx != SHN_UNDEF ? 'V' : 'v');
	return (sym->shndx != SHN_UNDEF ? 'W' : 'w');
}

char	get_flag(t_elfH *e, t_symbol sym, char (*pt[])(t_elfH *e, t_symbol *sym))
{
	char		flag;
    uint8_t		weak = sym.bind == STB_WEAK ? 1 : 0;
    uint8_t		undefined = sym.shndx == SHN_UNDEF ? 1 : 0;
    uint8_t		local = sym.bind == STB_LOCAL ? 1 : 0;

	if (!local)
		if ((flag = c_flag(&sym)) != NO_TYPE)
			return (flag);
	if (sym.bind == STB_GNU_UNIQUE)
		return ('U');
	if (weak)
		return (weak_flag64(&sym));
	if (sym.shndx != SHN_ABS && sym.shndx != SHN_COMMON)
	{
		if (local)
		{
			if ((flag = pt[0](e, &sym)) != NO_TYPE)
				return (flag);
		}
		else
		{
			if ((flag = pt[1](e, &sym)) != NO_TYPE)
				return (flag);
		}
	}
	if (sym.shndx == SHN_ABS)
		return (local ? 'a' : 'A');
	return ('?');
}
