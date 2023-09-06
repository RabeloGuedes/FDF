NAME = FDF

CC = cc

FLAGS = -Wall -Wextra -Werror

SRC_FILES = FDF.c

OBJS_FILES = $(SRC_FILES:.c=.o)

all: $(NAME)

$(NAME): $(notdir $(OBJS_FILES))
	@ar rc $(NAME) $(notdir $(OBJS_FILES))
	@norminette  

$(notdir $(OBJS_FILES)): $(SRC_FILES)
	@$(CC) -c $(CCFLAGS) -I ./inc $(SRC_FILES)

clean:
	@rm -rf $(notdir $(OBJS_FILES))

fclean: clean
	@rm -rf $(NAME)

re: fclean all
