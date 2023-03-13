#  |  |  ___ \    \  |         |
#  |  |     ) |  |\/ |   _  |  |  /   _ 
# ___ __|  __/   |   |  (   |    <    __/ 
#    _|  _____| _|  _| \__,_| _|\_\ \___|
#                              by jcluzet
################################################################################
#                                     CONFIG                                   #
################################################################################

NAME     := fract-ol
CC       := gcc
FLAGS    := -Wall -Wextra -Werror 
################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

SRCS        :=      main.c \
					mandelbrot.c \
					julia.c \
                          
OBJS        := $(SRCS:.c=.o)

%.o: %.c
	$(CC) -Wall -Wextra -Werror

################################################################################
#                                  Makefile  objs                              #
################################################################################

$(NAME): $(OBJ)
	$(CC) $(SRCS) MLX42/libmlx42.a -lglfw -L /Users/ljerinec/.brew/Cellar/glfw/3.3.8/lib/

home: $(OBJ)
	@make -C MLX42
	$(CC) $(SRCS) MLX42/libmlx42.a -lglfw -L /opt/homebrew/Cellar/glfw/3.3.8/lib/

all: ${NAME}

clean:
	@ ${RM} *.o */*.o */*/*.o

fclean:		clean
	@ ${RM} ${NAME}
	@ rm libmlx.a
	@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"

re:	fclean all

.PHONY:	all clean fclean re
