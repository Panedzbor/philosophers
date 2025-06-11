
# target
NAME = philo

# complier and flags
CC = cc
CFLAGS = -g -Wall -Wextra -Werror -I.
LFLAGS = #-Llibft -lft -lmlx -lXext -lX11 -lm

# files
SRC = main.c ph_atoi.c
#SRC_BON = main_bonus.c check_functions_bonus.c display_current_sprite_bonus.c display_sprites_bonus.c draw_map_bonus.c \
	game_termination_bonus.c key_hook_bonus.c loop_hook_bonus.c parse_map_bonus.c place_enemies_bonus.c save_map_bonus.c \
	utils_bonus.c validate_map_bonus.c display_score_bonus.c
OBJ = $(SRC:.c=.o)
#OBJ_BON = $(SRC_BON:.c=.o)
HEADER = philo.h
#HEADER_BON = so_long_bonus.h

# rules
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LFLAGS) -o $(NAME)

#bonus: libft $(OBJ_BON)
#	$(CC) $(CFLAGS) $(OBJ_BON) $(LFLAGS) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

#%_bonus.o: %_bonus.c $(HEADER_BON)
#	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJ_BON)

fclean: clean
	rm -f $(NAME)

re: fclean all

#reb: fclean bonus

.PHONY: all clean fclean re libft bonus reb
