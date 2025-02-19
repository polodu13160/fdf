.PHONY: all clean fclean re init

CC = cc
#FLAGS = -Wall -Wextra -Werror -g3
FLAGS = -Wall -Wextra -g3 
FLAGSMLX = -L$(MLX_PATH) -lmlx -lX11 -lXext -lm
NAME = fdf
LIBFT_PATH = srcs/libft_updated
MLX = $(MLX_PATH)/libmlx_Linux.a
MLX_PATH = srcs/minilibx-linux
LIBFT = $(LIBFT_PATH)/libft.a

SRCS = srcs/main.c srcs/parsing.c srcs/parsing_pt2.c 
OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(MLX) $(LIBFT) $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(FLAGSMLX) $(LIBFT)

$(LIBFT): $(LIBFT_PATH)/*c $(LIBFT_PATH)/libft.h
	$(MAKE) -C $(LIBFT_PATH)

$(MLX):
	$(MAKE) -C $(MLX_PATH)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_PATH) clean
	$(MAKE) -C $(MLX_PATH) clean
	

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)
	rm -f $(MLX)
	rm -f $(MLX_PATH)/libmlx.a

	

re: fclean all

init:
	$(MAKE) re
	$(MAKE) clean



#  make && valgrind --track-origins=yes ./fdf ./maps/test_maps/42.fdf 