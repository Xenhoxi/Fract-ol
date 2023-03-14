################################################################################
#                                     CONFIG                                   #
################################################################################

NAME     := fract-ol
PRINT_PREFIX	= \033[1m\033[38;5;240m[\033[0m\033[38;5;250m$(NAME)\033[1m\033[38;5;240m] \033[38;5;105m~\033[0m

CC       := gcc
FLAGS    := -Wall -Wextra -Werror 

################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

SRCS =	sources/fract-ol.c \
		sources/fractales/mandelbrot.c \
		sources/fractales/julia.c \
                          
OBJS = $(SRCS:%.c=%.o)
# MLX42_INC = -lglfw -L /Users/ljerinec/.brew/Cellar/glfw/3.3.8/lib/
MLX42_INC = -lglfw -L /opt/homebrew/Cellar/glfw/3.3.8/lib/
MLX42_DIR = MLX42/libmlx42.a

################################################################################
#                                  Makefile  objs                              #
################################################################################

all: ${NAME}

$(NAME): libft $(OBJS) $(SRCS)
	@echo "$(PRINT_PREFIX)\033[0;38;5;226m Compiling MLX42 \033[0m\n"
	@make -C MLX42
	@echo "$(PRINT_PREFIX)\033[0;38;5;226m Compiling Fract-ol \033[0m\n"
	$(CC) -o $(NAME) $(OBJS) $(MLX42_DIR) $(MLX42_INC)
	@echo "$(PRINT_PREFIX)\033[0;38;5;226m Done \033[0m\n"

home: libft $(OBJS) $(SRCS)
	@echo "$(PRINT_PREFIX)\033[0;38;5;226m Compiling MLX42 \033[0m\n"
	@make -C MLX42
	@echo "$(PRINT_PREFIX)\033[0;38;5;226m Compiling Fract-ol \033[0m\n"
	$(CC) -o $(NAME) $(OBJS) $(MLX42_DIR) $(MLX42_INC)
	@echo "$(PRINT_PREFIX)\033[0;38;5;226m Done \033[0m\n"

libft:
	@echo "$(PRINT_PREFIX)\033[0;38;5;226m Compiling libft \033[0m\n"
	@make -C includes/libft

clean:
	@make -C includes/libft clean
	@make -C MLX42 clean
	@echo "$(PRINT_PREFIX)\033[0;38;5;226m Cleaning \033[0m\n"
	@rm -f $(OBJECTS)
	@echo "$(PRINT_PREFIX)\033[0;38;5;226m Done \033[0m\n"

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C includes/libft fclean

re: fclean home

.PHONY: all clean fclean re
