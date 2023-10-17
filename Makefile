NAME = fdf

LIBFT_DIR = libft
LIBFT = libft/libft.a

MINILIBX_DIR = .minilibx-linux
MINILIBX = .minilibx-linux/libmlx.a

CC = cc

CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address,undefined
INC_FLAGS = -I ./inc -I $(LIBFT_DIR)/inc -I $(MINILIBX_DIR)/
PROGRAM_LIBS = -L$(LIBFT_DIR) -lft -L$(MINILIBX_DIR) -lmlx_Linux -L/usr/lib -lXext -lX11 -lz -lm 

ERRORS_DIR = errors/
ERRORS_FILES = $(ERRORS_DIR)handle_error.c $(ERRORS_DIR)handle_file_manipulation.c

UTILS_DIR = utils/
UTILS_FILES = $(UTILS_DIR)file_name_checker.c $(UTILS_DIR)free_data_structures.c

PROJECTION_DIR = projection/
PROJECTION_FILES = 	$(PROJECTION_DIR)center_projection.c $(PROJECTION_DIR)controls.c $(PROJECTION_DIR)rebuild_projection.c\
					$(PROJECTION_DIR)rotate_grid.c $(PROJECTION_DIR)set_values.c $(PROJECTION_DIR)redo.c $(PROJECTION_DIR)keys.c

QUEUE_DIR = queue/
QUEUE_FILES = $(QUEUE_DIR)node.c $(QUEUE_DIR)queue.c

LINES_DIR = lines/
LINES_FILES = $(LINES_DIR)draw_lines.c $(LINES_DIR)generate_lines.c

WINDOW_DIR = window/
WINDOW_FILES = $(WINDOW_DIR)window.c $(WINDOW_DIR)destroy_window.c

HANDLE_MAP = handle_map/
HANDLE_MAP_FILES = $(HANDLE_MAP)parse_map.c $(HANDLE_MAP)map_config.c $(HANDLE_MAP)map.c

SRC_DIR = src
SRC_FILES =	$(PROJECTION_FILES)	$(ERRORS_FILES) $(UTILS_FILES)\
			$(QUEUE_FILES) $(LINES_FILES) $(HANDLE_MAP_FILES)\
			$(WINDOW_FILES)

OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC_FILES:%.c=%.o))

all: $(NAME)

$(NAME): $(OBJ)
	@make -s -C $(LIBFT_DIR)
	@make -s -C $(MINILIBX_DIR) 2> /dev/null 1> /dev/null
	@$(CC) $(CFLAGS) $(INC_FLAGS) $(OBJ) $(SRC_DIR)/$(NAME).c -o $(NAME) $(PROGRAM_LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) -c $(CFLAGS) $(INC_FLAGS) $< -o $@

clean:
	@make clean -s -C $(LIBFT_DIR)
	@make clean -s -C $(MINILIBX_DIR) > /dev/null
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME) $(LIBFT)

re: fclean all
