#  |  |  ___ \    \  |         |
#  |  |     ) |  |\/ |   _  |  |  /   _ 
# ___ __|  __/   |   |  (   |    <    __/ 
#    _|  _____| _|  _| \__,_| _|\_\ \___|
#                              by jcluzet
################################################################################
#                                     CONFIG                                   #
################################################################################

PRINT_NAME		= fract-ol
PRINT_PREFIX	= \033[1m\033[38;5;240m[\033[0m\033[38;5;250m$(PRINT_NAME)\033[1m\033[38;5;240m] \033[38;5;105m~\033[0m

NAME     := fract-ol
CC       := gcc
FLAGS    := -Wall -Wextra -Werror 

################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

SRCS =	sources/fract-ol.c \
		sources/fractales/mandelbrot.c \
		sources/fractales/julia.c \
                          
OBJS = $(SRCS:%.c=%.o)

%.o: %.c
	$(CC) -Wall -Wextra -Werror

################################################################################
#                                  Makefile  objs                              #
################################################################################

libft:
	@make -C includes/libft

$(NAME): $(OBJ)
	$(CC) $(SRCS) MLX42/libmlx42.a -lglfw -L /Users/ljerinec/.brew/Cellar/glfw/3.3.8/lib/

home: $(OBJ)
	@echo "$(PRINT_PREFIX)\033[0;38;5;226m Compiling \033[0m\n"
	@make -C MLX42
	$(CC) -o $(NAME) $(OBJS) MLX42/libmlx42.a -lglfw -L /opt/homebrew/Cellar/glfw/3.3.8/lib/
	@echo "$(PRINT_PREFIX)\033[0;38;5;226m Done \033[0m\n"


all: ${NAME}

clean:
	@make -C includes/libft clean
	@echo "$(PRINT_PREFIX)\033[0;38;5;226m Cleaning \033[0m\n"
	@rm -f $(OBJECTS)
	@echo "$(PRINT_PREFIX)\033[0;38;5;226m Done \033[0m\n"

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C includes/libft fclean

re: fclean all

.PHONY: all clean fclean re
