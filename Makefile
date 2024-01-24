NAME = pipex
DEBUG_NAME = pipex_debug
CFLAGS = -Wall -Werror -Wextra
DFLAGS = -g3
CC = gcc
VALGRIND_LOG = valgrind.log

# Paths for libraries
LIB_PATH = ./lib/libft
LIB_NAME = libft.a
LIB_PRINTF_NAME = libftprintf.a
LIB_PRINTF_PATH = ./lib/ft_printf

# Colors Definition 
GREEN = "\033[32;1m"
RED = "\033[31;1m"
CYAN = "\033[36;1;3;208m"
WHITE = "\033[37;1;4m"
COLOR_LIMITER = "\033[0m"

# Paths definitions
HEADER_PATH = ./includes
OBJ_PATH = ./obj/
SOURCES_PATH = ./src/
SOURCES = heap.c  main.c  safety.c  shell.c  stack.c  utils.c

ifdef WITH_DEBUG
  NAME = $(DEBUG_NAME)
  CFLAGS = $(DFLAGS)
  OBJ_PATH = ./obj_debug/
endif

OBJECTS = $(addprefix $(OBJ_PATH), $(SOURCES:%.c=%.o))

all: libft libftprintf $(OBJ_PATH) $(NAME)

libft:
	@make bonus --directory=$(LIB_PATH) --no-print-directory
	
libftprintf:
	@make --directory=$(LIB_PRINTF_PATH) --no-print-directory

debug:
	@make WITH_DEBUG=TRUE --no-print-directory

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

$(NAME): $(OBJECTS) libft libftprintf
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) -L $(LIB_PATH) -L $(LIB_PRINTF_PATH) -lft -lftprintf
	@echo $(CYAN)" ----------------------------------------------"$(COLOR_LIMITER)
	@echo $(CYAN)"| PIPEX executable was created successfully!! |"$(COLOR_LIMITER)
	@echo $(CYAN)"----------------------------------------------"$(COLOR_LIMITER)
	@echo " "

$(OBJ_PATH)%.o: $(SOURCES_PATH)%.c $(HEADER_PATH)/pipex.h
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
	./$(DEBUG_NAME) ./tests/infile "cat" "grep pipe" ./tests/outfile
	@cat $(VALGRIND_LOG)

nor: 
	@echo $(GREEN)[Running Norminette]$(COLOR_LIMITER)
	@norminette -R CheckForbiddenSourceHeader $(SOURCES_PATH) $(HEADER_PATH)
	@echo $(GREEN)[Running Norminette on Libft]$(COLOR_LIMITER)
	@norminette -R CheckForbiddenSourceHeader $(LIB_PATH)

tester: all
	@echo $(GREEN)[Running tests]$(COLOR_LIMITER)
	@wget https://raw.githubusercontent.com/jos-felipe/pipex/self/tester.sh > /dev/null 2>&1
	@chmod +x tester.sh
	@./tester.sh

clean:
	@echo $(RED)[Removing Objects]$(COLOR_LIMITER)
	-rm -rf $(OBJ_PATH)
	@echo $(RED)[Removing test files]$(COLOR_LIMITER)
	-rm -rf ./tmp

fclean: clean
	@echo $(RED)[Removing $(NAME) executable]$(COLOR_LIMITER)
	@make fclean -C $(LIB_PATH) --no-print-directory
	@make fclean -C $(LIB_PRINTF_PATH) --no-print-directory
	@rm -rf $(NAME)
	@rm -rf $(VALGRIND_LOG)

re: fclean
	@make --no-print-directory

.PHONY: all clean fclean re libft valgrind debug tester nor qa
