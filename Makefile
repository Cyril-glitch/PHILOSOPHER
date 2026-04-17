NAME = philo

CC = clang
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -g
OBJ_DIR = obj


SRC = src/main.c \
	  src/utils.c \
	  src/timelogs.c \
	  src/init.c \
	  src/routine.c \
	  src/actions.c \
	  src/monitoring.c \
	  src/cleaning.c 

OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

VPATH = src:.

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -lpthread

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all