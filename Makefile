NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
OBJ_DIR = obj

LIBDIR = ./libft/
LIB = ./libft/lib/libft.a

SRC = src/main.c \
	  src/init.c

OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

VPATH = src:.

all: $(NAME)

$(NAME): $(OBJ) $(LIB)
	$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB) :
	make bonus -C $(LIBDIR)

.PHONY: all clean fclean re

clean:
	rm -rf $(OBJ_DIR)
	make clean -C $(LIBDIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBDIR)

re: fclean all