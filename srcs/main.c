#include <sys/mman.h> //mmap/munmap
#include <sys/types.h> //fstat / open
#include <sys/stat.h> //fstat / open
#include <fcntl.h> //fstat

#include <stdlib.h> //exit

#include <stdio.h> //printf

#include "ft_nm.h"

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

size_t	ft_strlen(const char *s)
{
	int i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

void	*init_nm(char *path, struct stat *buf)
{
	void	*ptr;
	int		fd;
	int8_t	error;
	
	error = SUCCESS;
	if ((fd = open(path, O_RDONLY)) == ERROR)
	{
		fprintf(stderr, "%s: can't open file: %s\n", NAME, path);
		return (NULL);
	}
	if ((fstat(fd, buf) != SUCCESS))
	{
		fprintf(stderr, "%s: Critical error : fstat failed\n", NAME);
		error = ERROR;
	}
	if (!error && ((ptr = mmap(0, buf->st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED))
	{
		fprintf(stderr, "%s: Critical error : mmap failed\n", NAME);
		error = ERROR;
		return (NULL);
	}
	if ((close(fd) != SUCCESS))
	{
		fprintf(stderr, "%s: Critical error : close failed\n", NAME);
		error = ERROR;
	}
	if (error)
		return (NULL);
	return (ptr);
}

void	check_file_type(Elf64_Ehdr *elf, char *name_file)
{
		if (elf->e_type != ET_EXEC &&
			elf->e_type != ET_REL &&
		 	elf->e_type != ET_DYN)
		{
			fprintf(stderr, "nm: %s: File format not recognized\n", name_file);
			debug_print_type(elf->e_type);
		}
}

int		is_not_elf(Elf64_Ehdr *elf, char *name_file)
{
	if (elf->e_ident[EI_MAG0] != ELFMAG0 ||
		elf->e_ident[EI_MAG1] != ELFMAG1 ||
		elf->e_ident[EI_MAG2] != ELFMAG2 ||
		elf->e_ident[EI_MAG3] != ELFMAG3)
	{
		fprintf(stderr, "%s: %s: File format not recognized\n", NAME, name_file);
		return (ERROR);
	}
	return (SUCCESS);
}

void	print_symlink(t_elfH *e, t_symbol *lst, char (*pt[])(t_elfH *e, t_symbol *sym), uint8_t field_value)
{

	while (lst)
	{
		if (lst->value)
			printf("%0*lx %c %s\n", field_value, lst->value, get_flag(e, *lst, pt), lst->name);
		else
			printf("%*c %c %s\n", field_value, ' ', get_flag(e, *lst, pt), lst->name);
		lst = lst->next;
	}
}

int8_t	init_elf(t_elfH *elf, char *name_file)
{
	if (is_xbit(elf) == 32)
	{
		elf->e32.ehdr = elf->file;
		elf->e32.shdr = elf->file + elf->e32.ehdr->e_shoff;
		elf->sh_index = find_symtab32(elf->file, &elf->e32);
	}
	else
	{
		elf->e64.ehdr = elf->file;
		elf->e64.shdr = elf->file + elf->e64.ehdr->e_shoff;
		elf->sh_index = find_symtab64(elf->file, &elf->e64);
	}
	if (elf->sh_index == ERROR)
		return (error_no_symbol(name_file));
	if (((char *)elf->file)[EI_DATA] == ELFDATA2LSB)
		elf->endianess = LITTLE_E;
	else
		elf->endianess = BIG_E;
	check_file_type(elf->file, name_file); //quel type ne faut il pas gerer ? 
	return (SUCCESS);
}

int		ft_nm(char *name_file)
{
	t_elfH		elf = {0};
	t_symbol	*lst;
	char		(*pt[2])(t_elfH *e, t_symbol *sym);
	uint8_t		field_value;
	struct stat	buf = {0};

	if ((elf.file = init_nm(name_file, &buf)) == NULL)
		return (ERROR);
	if (is_not_elf(elf.file, name_file))
		return (ERROR);
	if (init_elf(&elf, name_file) == ERROR)
	   return (0);// no sym == ret = 0
	if (elf.xbit == 64)
	{
		 lst = find_symlink64(&elf, &elf.e64); //go free ici
		 pt[0] = local_flag64;
		 pt[1] = global_flag64;
		 field_value = 16;
	}
	else
	 {
		 lst = find_symlink32(&elf, &elf.e32); //go free ici
		 pt[0] = local_flag32;
		 pt[1] = global_flag32;
		 field_value = 8;
	 }
	print_symlink(&elf, lst, pt, field_value);
	clean_lst_symbol(&lst);
	if (munmap(elf.file, buf.st_size) < 0)
	{
		fprintf(stderr, "%s: Critical error : munmap failed\n", NAME);
		return (1);// critical error -> doit tout stopper
	}
	 return (SUCCESS);
}

int		main(int ac, char **av)
{
	int		ret;

	if (ac == 1)
		ret = ft_nm("a.out");
	else if (ac == 2)
		ret = ft_nm(av[1]);
	else
		for (uint8_t i = 1; i < ac; i++)
		{
			printf("\n%s: %s:\n", NAME, av[i]);
			ret += ft_nm(av[i]);
		}
	if (ret)
		return (FAIL);
	return (SUCCESS);
}
