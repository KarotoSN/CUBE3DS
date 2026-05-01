NAME        = cube
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g3

LIBFT_PATH  = ./libft
LIBFT       = $(LIBFT_PATH)/libft.a

MLX_PATH    = ./minilibx-linux
MLX         = $(MLX_PATH)/libmlx.a

MLX_FLAGS   = -L$(MLX_PATH) -lmlx -L/usr/lib -I$(MLX_PATH) -lXext -lX11 -lm

SRCS        = main2.c \
				UnrealEngine/init_mlx.c \
				UnrealEngine/init_engine.c \
				UnrealEngine/input_manager.c \
				UnrealEngine/drawland.c \
				UnrealEngine/mouse.c \
				Parsing/analyse.c \
				Parsing/color.c \
				Parsing/map_check.c \
				Parsing/parse_all.c \
				gnl/get_next_line.c \
				gnl/get_next_line_utils.c 



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
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo "✅ Terminé ! Lance avec : ./$(NAME) + fichier.ber"

%.o: %.c
	$(CC) $(CFLAGS) -I. -I$(MLX_PATH) -c $< -o $@

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