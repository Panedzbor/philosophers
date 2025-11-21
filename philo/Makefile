
# target
NAME = philo

# complier and flags
CC = cc
CFLAGS = -g -Wall -Wextra -Werror -I. -pthread
TFLAGS = -g -Wall -Wextra -I. -pthread

# files
SRC = main.c srcs/death_checker.c srcs/mem_allocator.c \
		srcs/mem_cleaner.c srcs/mem_initializer.c \
		srcs/mem_initializer_ph.c srcs/mutex_print.c \
		srcs/parser.c srcs/phil_lifecycle.c \
		srcs/thread_operations.c srcs/time_converter.c \
		srcs/utils.c srcs/get_value.c srcs/checks.c \
		srcs/helper_funcs/ft_isdigit.c \
		srcs/helper_funcs/ft_putstr_fd.c \
		srcs/helper_funcs/ph_atoi.c \
		srcs/helper_funcs/ph_sleep.c
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
