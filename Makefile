NAME        = cube
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g3

LIBFT_PATH  = ./libft
LIBFT       = $(LIBFT_PATH)/libft.a

MLX_PATH    = ./minilibx-linux
MLX         = $(MLX_PATH)/libmlx.a

MLX_FLAGS   = -L$(MLX_PATH) -lmlx -L/usr/lib -I$(MLX_PATH) -lXext -lX11 -lm

SRCS        = main2.c \
				2_UnrealEngine/init_mlx.c \
				2_UnrealEngine/init_engine.c \
				2_UnrealEngine/input_manager.c \
				2_UnrealEngine/drawland.c \
				2_UnrealEngine/mouse.c \
				2_UnrealEngine/key_manage.c \
				1_Parsing/analyse.c \
				1_Parsing/color.c \
				1_Parsing/map_check.c \
				1_Parsing/parse_all.c \
				1_Parsing/init_player.c \
				gnl/get_next_line.c \
				gnl/get_next_line_utils.c \
				Free/free.c \
				Free/close_game.c \
				3_Minimap/minimap.c \
				4_Sprites/find_sprite.c \
				4_Sprites/calcul.c



OBJS        = $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT):
	@echo "📚 Compilation de la Libft..."
	@make -C $(LIBFT_PATH)
$(MLX):
	@echo "🎮 Compilation de la MiniLibX..."
	@make -C $(MLX_PATH)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	@echo "🔨 Compilation de $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo "✅ Terminé ! Lance avec : ./$(NAME) + fichier.ber"

%.o: %.c
	@$(CC) $(CFLAGS) -I. -I$(MLX_PATH) -c $< -o $@

clean:
	@echo "🧹 Nettoyage des objets..."
	@rm -f $(OBJS)
	@make clean -C $(MLX_PATH)
	@make clean -C $(LIBFT_PATH)

fclean: clean
	@echo "🗑️ Suppression de l'exécutable..."
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_PATH)

re: fclean all

.PHONY: all clean fclean re