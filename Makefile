NAME        = cube
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g3

MLX_PATH    = ./minilibx-linux
MLX         = $(MLX_PATH)/libmlx.a

MLX_FLAGS   = -L$(MLX_PATH) -lmlx -L/usr/lib -I$(MLX_PATH) -lXext -lX11 -lm

SRCS        = main2.c \
				init_mlx.c \
				init_engine.c \
				input_manager.c \
				drawland.c \

OBJS        = $(SRCS:.c=.o)

all: $(NAME)

$(MLX):
	@echo "🎮 Compilation de la MiniLibX..."
	@make -C $(MLX_PATH)

$(NAME): $(OBJS) $(MLX)
	@echo "🔨 Compilation de $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)
	@echo "✅ Terminé ! Lance avec : ./$(NAME) + fichier.ber"

%.o: %.c
	$(CC) $(CFLAGS) -I. -I$(MLX_PATH) -c $< -o $@

clean:
	@echo "🧹 Nettoyage des objets..."
	@rm -f $(OBJS)
	@make clean -C $(MLX_PATH)

fclean: clean
	@echo "🗑️ Suppression de l'exécutable..."
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re