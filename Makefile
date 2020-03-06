NAME = wolf3d

SRC = main.c get_map.c init_and_usage.c events.c

OBJ = $(SRC:.c=.o)

HEADER = wolf3d.h

FLAGS = -Wall -Wextra -Werror

MLX_FLAGS = -L ./mlx/ -lmlx -framework OpenGL -framework AppKit


GLFW = -L glfwPre/lib-macos -lglfw

GLEW = -L glew/lib -lGLEW -framework OpenGL




GLFW_LOC := $(shell brew --prefix glfw)
##GLFW_INC := $(GLFW_LOC)/include/
GLFW_LINK := -L $(GLFW_LOC)/lib/ -lglfw

GLEW_LOC := $(shell brew --prefix glew)
##GLEW_INC := $(GLEW_LOC)/include/
GLEW_LINK := -L $(GLEW_LOC)/lib/ -lGLEW 




MLX_FLAGS = -L ./mlx/ -lmlx -framework OpenGL -framework AppKit


$(NAME): $(OBJ)
	@make -C libft/
	@gcc $(FLAGS) $(SRC) -o $(NAME) -L libft -lft $(GLFW_LINK) $(GLEW_LINK) -framework OpenGL $(MLX_FLAGS)

%.o:%.c $(HEADER)
	@gcc $(FLAGS) -I . -c $< -o $@

clean:
	@/bin/rm -f *~
	@/bin/rm -f $(OBJ)
	@make -C libft/ clean

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C libft/ fclean

all: $(NAME)

re: fclean all

.PHONY: clean fclean all re
