NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror 
OBJ_DIR = obj


SRC = src/main.c \
	  src/init.c \
	  src/atoi.c \
	  src/error.c \
	  src/time.c \
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