NAME = fdf

LIBFT_DIR = libft
LIBFT = libft/libft.a

MINILIBX_DIR = minilibx-linux
MINILIBX = minilibx-linux/libmlx.a

CC = cc

CFLAGS = -Wall -Wextra -Werror -fsanitize=address,undefined
INC_FLAGS = -I ./inc -I $(LIBFT_DIR)/inc -I $(MINILIBX_DIR)/
PROGRAM_LIBS = -L$(LIBFT_DIR) -lft -L$(MINILIBX_DIR) -lmlx -L -lm

SRC_DIR = src
SRC_FILES = free_matrix.c parse_map.c handle_file_manipulation.c window.c

OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC_FILES:%.c=%.o))

all: $(NAME)

$(NAME): $(OBJ)
	@make -s -C $(LIBFT_DIR)
	@make -s -C $(MINILIBX_DIR) 2> /dev/null 1> /dev/null
	@$(CC) $(CFLAGS) $(INC_FLAGS) $(OBJ) $(SRC_DIR)/$(NAME).c -o $(NAME) $(PROGRAM_LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) -c $(CFLAGS) $(INC_FLAGS) $< -o $@

clean:
	@make clean -s -C $(LIBFT_DIR)
	@make clean -s -C $(MINILIBX_DIR) > /dev/null
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME) $(LIBFT)

re: fclean all
