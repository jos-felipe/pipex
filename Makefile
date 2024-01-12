NAME = pipex
DFLAGS = -Wall -Werror -Wextra -g3
CFLAGS = -Wall -Werror -Wextra -O3 -fomit-frame-pointer -finline-functions
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
BIN_PATH = ./bin/
DEP_PATH = ./dep/
MANDATORY_SOURCES_PATH = ./src/mandatory/

MANDATORY_SOURCES = \
	clear.c \
	commands.c \
	error.c \
	execute.c \
	main.c \
	start_files.c

OBJECTS = $(addprefix $(BIN_PATH), $(MANDATORY_SOURCES:%.c=%.o))
# OBJECTS = $(addprefix $(BIN_PATH), $(MANDATORY_SOURCES:%.c=%.o))
# DEP = $(MANDATORY_SOURCES:%.c=%.d)
DEP = $(addprefix $(DEP_PATH), $(MANDATORY_SOURCES:%.c=%.d))

all: libft $(BIN_PATH) $(DEP_PATH) $(NAME)

libft:
	@make -C $(LIB_PATH) --no-print-directory

$(BIN_PATH):
	@mkdir -p $(BIN_PATH)

$(DEP_PATH):
	@mkdir -p $(DEP_PATH)

$(NAME): $(OBJECTS) $(DEP)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) -L $(LIB_PATH) -lft
	@echo $(CYAN)" ----------------------------------------------"$(COLOR_LIMITER)
	@echo $(CYAN)"| PIPEX executable was created successfully!! |"$(COLOR_LIMITER)
	@echo $(CYAN)"----------------------------------------------"$(COLOR_LIMITER)
	@echo " "

-include $(DEP)
clear.o: src/mandatory/clear.c includes/pipex.h includes/../lib/libft/libft.h
	

$(BIN_PATH)%.o: $(MANDATORY_SOURCES_PATH)%.c
	@echo $(GREEN)[Compiling]$(COLOR_LIMITER) $(WHITE)$(notdir $(<))...$(COLOR_LIMITER)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER_PATH)
	@echo " "

$(DEP_PATH)%.d: $(MANDATORY_SOURCES_PATH)%.c
	@echo $(RED)[Generating Prerequisites]$(COLOR_LIMITER) $(WHITE)$(notdir $(<))...$(COLOR_LIMITER)
	$(CC) -MMD -MP -c $< -MF $@ -I $(HEADER_PATH)
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

clean:
	@echo $(RED)[Removing Objects]$(COLOR_LIMITER)
	@make clean -C $(LIB_PATH) --no-print-directory
	@rm -rf $(BIN_PATH)
	@echo $(RED)[Removing Dependencies]$(COLOR_LIMITER)
	# @rm -rf $(DEP_PATH)

fclean: clean
	@echo $(RED)[Removing $(NAME) executable]$(COLOR_LIMITER)
	@make fclean -C $(LIB_PATH) --no-print-directory
	@rm -rf $(NAME)
	@rm -rf $(NAME_BONUS)
	@rm -rf $(VALGRIND_LOG)

re: fclean
	@make --no-print-directory

debug:
	@make WITH_DEBUG=TRUE --no-print-directory

debug_re: fclean
	@make WITH_DEBUG=TRUE --no-print-directory

.PHONY: all clean fclean re libft valgrind debug debug_re
