NAME = my_nm
NAMEDB = my_nm_db

# Reset
NC=\033[0m

# Regular Colors
BLACK=\033[0;30m
RED=\033[0;31m
GREEN =\033[32m
YELLOW=\033[0;33m
BLUE=\033[0;34m
PURPLE=\033[0;35m
CYAN=\033[0;36m
WHITE=\033[0;37m

## SRCS ##

SRC_FILE += main.c
SRC_FILE += elfx32.c
SRC_FILE += elfx64.c
SRC_FILE += sym_list.c
SRC_FILE += flags.c
SRC_FILE += errors.c
SRC_FILE += dev.c

## INCLUDES ##

INC_FILE += ft_nm.h


CC = clang
COMPILE = $(CC) -c
COMPILEDB = $(CC) -g3

MKDIR = mkdir -p
CLEANUP = rm -rf

DSYN = $(NAMEDB).dSYM

OPATH = objs/
SPATH = srcs/
IPATH = includes/

#WFLAGS = -Wall -Werror -Wextra
IFLAGS = -I $(IPATH)
CFLAGS = $(WFLAGS) $(IFLAGS)
DBFLAGS = -fsanitize=address

OBJ = $(patsubst %.c, %.o, $(SRC_FILE))

SRCS = $(addprefix $(SPATH),$(SRC_FILE))

OBJS = $(addprefix $(OPATH),$(OBJ))

INCS = $(addprefix $(IPATH),$(INCLUDES))

all : $(NAME)

$(NAME) : $(OPATH) $(OBJS) Makefile
	$(CC) -o $@ $(OBJS)
	printf "$(GREEN)$@ is ready.\n$(NC)"

$(OBJS) : $(OPATH)%.o : $(SPATH)%.c
	$(COMPILE) $(CFLAGS) $< -o $@

$(OPATH) :
	$(MKDIR) $@

debug :
	$(COMPILEDB) $(DBFLAGS) $(CFLAGS) -o $(NAMEDB) $(SRCS) $^
	printf "$(GREEN)$(NAMEDB) is ready.\n$(NC)"


clean :
	$(CLEANUP) $(OBJS)
	$(CLEANUP) $(OPATH)
	$(CLEANUP) $(DSYN)
	printf "$(RED)Directory $(NAME) is clean\n$(NC)"

fclean : clean
	$(CLEANUP) $(OPATH)
	$(CLEANUP) $(NAME)
	$(CLEANUP) $(NAMEDB)
	printf "$(RED)$(NAME) is delete\n$(NC)"

re : fclean all

FORCE:

.PHONY: all clean fclean norme re debug FORCE
.SILENT:
