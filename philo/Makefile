
# target
NAME = philo

# complier and flags
CC = cc
CFLAGS = -g -Wall -Wextra -Werror -I. -pthread
TFLAGS = -g -Wall -Wextra -I. -pthread

# files
#SRC = main.c srcs/parser.c srcs/helper_funcs/ph_atoi.c srcs/helper_funcs/ph_atoi.c
SRC = $(wildcard *.c) $(wildcard srcs/*.c) $(wildcard srcs/*/*.c)
OBJ_DIR = objs
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
HEADER = philo.h

# rules
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: %.c $(HEADER)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

test:
	$(CC) $(TFLAGS) $(SRC) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus test
