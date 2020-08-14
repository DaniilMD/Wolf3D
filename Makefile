NAME = wolf3d

SRC = main.c init_and_usage.c events.c define_map.c\
	wall_casting_funcs.c wall_casting_core.c floor_and_ceiling_casting.c\
	sprite_casting_funcs.c sprite_casting_core.c fog.c free.c movement.c\
	door_funcs_check_hit.c door_funcs_event.c minimap.c rotation.c norm.c\
	norm2.c norm3.c norm4.c\
	
SRC_DIR = src/
OBJ_DIR = obj/
INC_DIR = include/
LIB_DIR = libft/

HEADER =  wolf3d.h
MAC_KEYS = keys.h
LINUX_KEYS = linux_keys.h

ALL_HEADERS = $(HEADER) $(LINUX_KEYS) $(MAC_KEYS)

OBJ = $(SRC:.c=.o)

LIBFT = -L ./libft -lft

FLAGS = -Wall -Wextra -Werror

MLX_FLAGS = -L ./minilibx -lmlx -lXext -lX11

LINUX_EXTRA_FLAGS = -lm -pthread

vpath %.c $(SRC_DIR)
vpath %.o $(OBJ_DIR)
vpath %.h $(INC_DIR)

$(NAME): $(OBJ)
	make -C libft/
	gcc $(FLAGS) ${addprefix $(OBJ_DIR), $(OBJ)} $(LIBFT) $(MLX_FLAGS) $(LINUX_EXTRA_FLAGS) -o $(NAME)

${OBJ}:%.o:%.c $(ALL_HEADERS) | $(OBJ_DIR)
	gcc -c -I $(INC_DIR) -I $(LIB_DIR) $(FLAGS) $< -o ${addprefix $(OBJ_DIR), $@}

clean:
	/bin/rm -f *~
	/bin/rm -f $(OBJ)
	make -C libft/ clean

fclean: clean
	/bin/rm -f $(NAME)
	make -C libft/ fclean

all: $(NAME)

re: fclean all

makecl:
	make
	make clean

.PHONY: clean fclean all re makecl
.SILENT: all $(NAME) $(OBJ) clean fclean re makecl
