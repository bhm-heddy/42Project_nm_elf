#ifndef FT_NM_H
# define FT_NM_H



#include <stdint.h> // type 
#include <elf.h>
#include <unistd.h> //size_t + fstat

#include <string.h>// debug strcmp

# define NAME		"my_nm"

# define SUCCESS	0
# define FAIL		1
# define TRUE		1
# define FALSE		0
# define ERROR		-1

# define NO_TYPE	'?'


# define BIG_E		0
# define LITTLE_E	1

# define GF_SIZE	12
# define LF_SIZE	20

int g_my_errno;

typedef	struct	s_elf32
{
    Elf32_Ehdr *ehdr;
    Elf32_Shdr *shdr;
	Elf32_Sym	*sym;
}				t_elf32;

typedef	struct	s_elf64
{
    Elf64_Ehdr *ehdr;
    Elf64_Shdr *shdr;
	Elf64_Sym	*sym;
}				t_elf64;

typedef struct	s_elfH
{
	void *file;
	void *end;
    void *strtable;
	t_elf32		e32;
	t_elf64		e64;
    Elf64_Ehdr *ehdr;
    Elf64_Shdr *shdr;
	Elf64_Sym	*sym;
	uint8_t		endianess;
	uint8_t		xbit;
	int32_t		sh_index;
    size_t 		fsize;
}				t_elfH;

typedef struct	s_symbol
{
	char	*name;
	int32_t				type;
	uint8_t				bind;
	uint16_t			shndx;
	uint64_t				value;
	struct	s_symbol	*next;
}				t_symbol;

typedef	struct	s_flags
{
	int32_t		stt;
	Elf32_Word	sh_type;
	Elf32_Word	sh_flags;
	char		type;
}				t_flags;

// DEV FUNC 

void	print_sh_type(uint32_t i);
void	print_section(t_elfH *e);



size_t	ft_strlen(const char *s);
t_symbol	*find_symlink32(t_elfH *elf, t_elf32 *e32);
t_symbol	*find_symlink64(t_elfH *elf, t_elf64 *e64);
int32_t		find_symtab64(char *file, t_elf64 *e);
int32_t		find_symtab32(char *file, t_elf32 *e);

char	global_flag32(t_elfH *e, t_symbol *sym);
char	local_flag32(t_elfH *e, t_symbol *sym);
char	global_flag64(t_elfH *e, t_symbol *sym);
char	local_flag64(t_elfH *e, t_symbol *sym);



uint8_t		is_xbit(t_elfH *elf);
char	get_flag(t_elfH *e, t_symbol sym, char (*pt[])(t_elfH *e, t_symbol *sym));

void		create_lst_symbol(t_symbol **begin, t_symbol *elem);
void		clean_lst_symbol(t_symbol **begin);


int		error_no_symbol(char *name_file);
int		error_corrupted_file(char *name_file);
int		check_offset(void *ptr, void *end);






#endif
