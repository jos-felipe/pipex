NAME = pipex
DEBUG_NAME = pipex_debug
CFLAGS = -Wall -Werror -Wextra
DFLAGS = -g3
# CFLAGS = -Wall -Werror -Wextra
# ifdef WITH_DEBUG
# 	CFLAGS = $(DFLAGS)
# endif
VALGRIND_LOG = valgrind.log

# Paths for libraries
LIB_PATH = ./lib/libft
LIB_NAME = libft.a

# Colors Definition 
GREEN = "\033[32;1m"
RED = "\033[31;1m"
CYAN = "\033[36;1;3;208m"
WHITE = "\033[37;1;4m"
COLOR_LIMITER = "\033[0m"

# Paths Definitions
HEADER_PATH = ./includes
OBJ_PATH = ./obj/
# MANDATORY_SOURCES_PATH = ./src/mandatory/
MANDATORY_SOURCES_PATH = ./

# MANDATORY_SOURCES = \
	clear.c \
	commands.c \
	error.c \
	execute.c \
	main.c \
	start_files.c

MANDATORY_SOURCES = main.c

ifdef WITH_DEBUG
  NAME = $(DEBUG_NAME)
  CFLAGS = $(DFLAGS)
  OBJ_PATH = ./obj_debug/
endif

OBJECTS = $(addprefix $(OBJ_PATH), $(MANDATORY_SOURCES:%.c=%.o))

all: libft $(OBJ_PATH) $(NAME)

libft:
	@make --directory=$(LIB_PATH) --no-print-directory

debug:
	@make WITH_DEBUG=TRUE --no-print-directory

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

$(NAME): $(OBJECTS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) -L $(LIB_PATH) -lft
	@echo $(CYAN)" ----------------------------------------------"$(COLOR_LIMITER)
	@echo $(CYAN)"| PIPEX executable was created successfully!! |"$(COLOR_LIMITER)
	@echo $(CYAN)"----------------------------------------------"$(COLOR_LIMITER)
	@echo " "

$(OBJ_PATH)%.o: $(MANDATORY_SOURCES_PATH)%.c $(HEADER_PATH)/pipex.h
	@echo $(GREEN)[Compiling]$(COLOR_LIMITER) $(WHITE)$(notdir $(<))...$(COLOR_LIMITER)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER_PATH)
	@echo " "

valgrind: debug
	@valgrind --leak-check=full \
	--show-reachable=yes \
	--track-fds=yes \
	--show-leak-kinds=all -s \
	--track-origins=yes \
	--log-file=$(VALGRIND_LOG) \
	./$(DEBUG_NAME) infile "cat" "grep teste" outfile
	# @cat $(VALGRIND_LOG)

qa: all
# @echo $(GREEN)[Running Norminette]$(COLOR_LIMITER)
# @norminette -R CheckForbiddenSourceHeader $(MANDATORY_SOURCES_PATH) $(HEADER_PATH)
# @echo $(GREEN)[Running Norminette on Libft]$(COLOR_LIMITER)
# @norminette -R CheckForbiddenSourceHeader $(LIB_PATH)
	@echo $(GREEN)[Comparing output with reference]$(COLOR_LIMITER)
	@-./$(NAME) infile "cat" "grep call" outfile.txt
	@-< infile cat | grep call > outfile_ref.txt
	@if diff outfile.txt outfile_ref.txt; then echo $(GREEN)"[OK]"$(COLOR_LIMITER); else echo $(RED)"[KO]"$(COLOR_LIMITER); fi
	@echo $(GREEN)[Non-existent input file]$(COLOR_LIMITER)
	@-./$(NAME) non_existent_file "cat" "grep call" outfile.txt
	@-< non_existent_file cat | grep call > outfile_ref.txt
	@if diff outfile.txt outfile_ref.txt; then echo $(GREEN)"[OK]"$(COLOR_LIMITER); else echo $(RED)"[KO]"$(COLOR_LIMITER); fi
# @echo $(GREEN)[Infile without read permission]$(COLOR_LIMITER)
# -./$(NAME) no_read_perm.txt "cat" "grep call" outfile
# echo $? > exit_status.txt
# -< no_read_perm.txt cat | grep call > outfile_ref
# echo $? > exit_status_ref.txt
# @diff exit_status.txt exit_status_ref.txt
# @echo $(GREEN)[Invalid outfile]$(COLOR_LIMITER)
# -./$(NAME) infile "cat" "grep call" /etc/passwd
# echo $? > exit_status.txt
# -< infile cat | grep call > /etc/passwd
# echo $? > exit_status_ref.txt
# @diff exit_status.txt exit_status_ref.txt
# @echo $(GREEN)[Invalid cmd1]$(COLOR_LIMITER)
# -./$(NAME) infile "1" "grep call" outfile
# echo $? > exit_status.txt
# -< infile 1 | grep call > outfile_ref
# echo $? > exit_status_ref.txt
# @echo $(GREEN)[Invalid cmd2]$(COLOR_LIMITER)
# -./$(NAME) infile "cat" "2" outfile
# echo $? > exit_status.txt
# -< infile cat | 2 > outfile_ref
# echo $? > exit_status_ref.txt
# @diff exit_status.txt exit_status_ref.txt


clean:
	@echo $(RED)[Removing Objects]$(COLOR_LIMITER)
	-rm -rf $(OBJ_PATH)

fclean: clean
	@echo $(RED)[Removing $(NAME) executable]$(COLOR_LIMITER)
	@make fclean -C $(LIB_PATH) --no-print-directory
	@rm -rf $(NAME)
	@rm -rf $(VALGRIND_LOG)

re: fclean
	@make --no-print-directory

.PHONY: all clean fclean re libft valgrind debug qa
