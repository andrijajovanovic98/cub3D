CC := cc
CFLAGS := -Wall -Wextra -Werror -Iincludes -g  #-fsanitize=leak,address,undefined
LDFLAGS = -lmlx -lXext -lX11 -lm

NAME := cub3D
NAME_BONUS := cub3D_bonus

LIBFT := libft/libft.a
LIBFT_DIR := libft/

SRC := src/main.c src/map_parsing/open.c src/map_parsing/elements.c src/utils.c\
	   src/map_parsing/read.c src/map_parsing/fill.c src/map_parsing/validate.c\
	   src/map_parsing/validate2.c src/map_parsing/utils.c src/events.c\
	   src/draw_map.c src/rending.c src/helpers.c src/raycasting.c\
	   src/set_pixel.c src/events2.c src/sprites.c src/utils2.c\
	   src/walls_check.c src/events3.c

SRC_BONUS := src_bonus/main_bonus.c src_bonus/map_parsing/open_bonus.c src_bonus/map_parsing/elements_bonus.c\
       src_bonus/utils_bonus.c src_bonus/map_parsing/read_bonus.c src_bonus/map_parsing/fill_bonus.c\
       src_bonus/map_parsing/validate_bonus.c\
       src_bonus/map_parsing/validate2_bonus.c src_bonus/map_parsing/utilss_bonus.c src_bonus/events_bonus.c\
       src_bonus/draw_map_bonus.c src_bonus/rending_bonus.c src_bonus/helpers_bonus.c src_bonus/raycasting_bonus.c\
       src_bonus/set_pixel_bonus.c src_bonus/events2_bonus.c src_bonus/sprites_bonus.c src_bonus/utils2_bonus.c\
	   src_bonus/walls_check_bonus.c src_bonus/events3_bonus.c

OBJ := $(SRC:.c=.o)
BONUS_OBJ := $(SRC_BONUS:.c=.o)
DEPS := $(SRC:.c=.d)
BONUS_DEPS := $(SRC_BONUS:.c=.d)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@echo " [✓]"
	@$(CC) $(CFLAGS) -lmlx -lXext -lX11 -o $(NAME) $(OBJ) $(LDFLAGS) $(LIBFT)

$(NAME_BONUS): $(LIBFT) $(BONUS_OBJ)
	@echo " [✓]"
	@$(CC) $(CFLAGS) -lmlx -lXext -lX11 -o $(NAME_BONUS) $(BONUS_OBJ) $(LDFLAGS) $(LIBFT)

bonus: CFLAGS += -D DOOR_VALID=1
bonus:  $(NAME_BONUS)

$(LIBFT):
	@make -sC $(LIBFT_DIR)

-include $(DEPS)
-include $(BONUS_DEPS)


%.o: %.c display
	@echo -n "■■■"
	@$(CC) -MMD -MP $(CFLAGS) -I. -c $< -o $@

%.o: %.c display
	@echo -n "■■■"
	@$(CC) -MMD -MP $(CFLAGS) -I. -c $< -o $@

display:
	@echo -n "Compiling objects: "

clean:
	@make -sC $(LIBFT_DIR) clean
	rm -f $(OBJ) $(DEPS) $(BONUS_OBJ) $(BONUS_DEPS)
	

fclean:
	@make -sC $(LIBFT_DIR) fclean
	rm -f $(OBJ) $(DEPS) $(BONUS_OBJ) $(BONUS_DEPS) $(NAME) $(NAME_BONUS)

re: fclean
	@make -s all

.PHONY: all clean fclean re bonus
.INTERMEDIATE: display
