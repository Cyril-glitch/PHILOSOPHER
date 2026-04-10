NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
OBJ_DIR = obj


SRC = src/main.c \
	  src/utils.c \
	  src/utils_2.c \
	  src/init.c \
	  src/routine.c

OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

VPATH = src:.

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all