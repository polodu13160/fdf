.PHONY: all clean fclean re init resize

CC = cc
FLAGS = -Wall -Wextra -Werror -g3 -I$(LIBFT_PATH)
#FLAGS = -Wall -Wextra -g3 
FLAGSMLX = -L$(MLX_PATH) -lmlx -lX11 -lXext -lm
FLAGLIBFT = -L$(LIBFT_PATH) -lft
NAME = fdf
LIBFT_PATH = libft
MLX = $(MLX_PATH)/libmlx_Linux.a
MLX_PATH = minilibx-linux
LIBFT = $(LIBFT_PATH)/libft.a

SRCS = srcs/main.c srcs/parsing.c srcs/parsing_pt2.c srcs/draw.c srcs/free.c srcs/line_to_point.c srcs/mlx_func.c srcs/trigo.c
OBJS = $(SRCS:%.c=%.o)

H = 900
L = 1920

all: $(NAME)

$(NAME): $(MLX) $(LIBFT) $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(FLAGSMLX) $(FLAGLIBFT)

$(LIBFT): $(LIBFT_PATH)/*c $(LIBFT_PATH)/libft.h
	$(MAKE) -C $(LIBFT_PATH)

$(MLX):
	$(MAKE) -C $(MLX_PATH)

%.o: %.c
	$(CC) $(FLAGS) -DHEIGHT=$(H) -DLENGTH=$(L) -c $< -o $@

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

resize: 
	$(MAKE) H=$(H) L=$(L) clean $(NAME)