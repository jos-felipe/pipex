NAME = pipex
DFLAGS = -g3
CFLAGS = -Wall -Werror -Wextra
ifdef WITH_DEBUG
	CFLAGS = $(DFLAGS)
endif
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

OBJECTS = $(addprefix $(OBJ_PATH), $(MANDATORY_SOURCES:%.c=%.o))

all: libft $(OBJ_PATH) $(NAME)

libft:
	@make --directory=$(LIB_PATH) --no-print-directory

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

valgrind: all
	@valgrind --leak-check=full \
	--show-reachable=yes \
	--track-fds=yes \
	--show-leak-kinds=all -s \
	--track-origins=yes \
	--log-file=$(VALGRIND_LOG) \
	./$(NAME) infile "cat" "grep teste" outfile
	@cat $(VALGRIND_LOG)

qa: all
	@echo $(GREEN)[Running Norminette]$(COLOR_LIMITER)
	@norminette -R CheckForbiddenSourceHeader $(MANDATORY_SOURCES_PATH) $(HEADER_PATH)
	@echo $(GREEN)[Running Norminette on Libft]$(COLOR_LIMITER)
	@norminette -R CheckForbiddenSourceHeader $(LIB_PATH)
	./$(NAME) infile "cat" "grep teste" outfile
	-./$(NAME) invalid_file "cat" "grep teste" outfile
	-./$(NAME) infile "cat" "grep teste" /etc/passwd
	-./$(NAME) infile "echo 1" "2" out

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

debug:
	@make WITH_DEBUG=TRUE --no-print-directory

.PHONY: all clean fclean re libft valgrind debug qa
