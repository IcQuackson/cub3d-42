# Compiled Files
NAME	=	cub3D
MLX		=	libmlx.a

# Compiler and flags
CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra -g# -fsanitize=address
MLXFLAGS	=	-Iminilibx-linux -Lminilibx-linux -lmlx -lmlx_Linux -L/usr/lib -lXext -lX11 -lm

# Directories
SRCDIR = srcs
OBJDIR = objs

# Files
SRCS	=	srcs/main.c srcs/init.c \
			srcs/file_parser.c srcs/init_textures.c srcs/raycasting.c srcs/map_checker.c \
			gnl/get_next_line.c srcs/utils.c srcs/player_parser.c srcs/texture_parser.c srcs/texture_checker.c  \
			srcs/create_map.c srcs/data_parser.c srcs/hooks.c srcs/movements.c
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
ARGS	= 	./maps/minecraft.cub

# Colors

DEFAULT = \033[0;39m
GRAY 	= \033[0;90m
RED 	= \033[0;91m
GREEN 	= \033[0;92m
YELLOW 	= \033[0;93m
BLUE 	= \033[0;94m
MAGENTA = \033[0;95m
CYAN 	= \033[0;96m
WHITE 	= \033[0;97m
CURSIVE	= \e[33;3m


all:		$(BIN_DIR) mlx $(NAME)

$(NAME): $(OBJS)
			@echo "$(CURSIVE)Compiling...$(DEFAULT)"
			@chmod 777 minilibx-linux/configure
			@$(MAKE) -C libft all
			$(CC) $(CFLAGS) $(OBJS) libft/libft.a -g -o $(NAME) $(MLXFLAGS)
			@echo "$(GREEN) Cub3D created successfully!$(DEFAULT)"

%.o: %.c
	$(CC) -Wall -Wextra -Werror -c $< -o $@ 

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

mlx:
			@echo "$(YELLOW)Compiling MLX..."
			@$(MAKE) -C minilibx-linux all

clean:
			@echo "$(BLUE)Cleaning...$(DEFAULT)"
			@$(MAKE) -C minilibx-linux clean
			@$(MAKE) -C libft clean
			@rm -rf $(OBJDIR)
			@echo "$(CYAN)Object Files Cleaned!$(DEFAULT)"

fclean:		clean
			@$(MAKE) -C libft fclean
			@rm -f $(NAME)
			@echo "$(BLUE)Executables Cleaned!$(DEFAULT)"

re:			fclean all
			@echo "$(MAGENTA)I cweeaned and rebuilt evewithing for u daddy UwU!$(DEFAULT)"

run: all
	 ./$(NAME) $(ARGS)

test_val_wrong_map:	all
	@for map_file in ./maps/wrong/*.cub; do \
		echo "$$map_file"; \
		valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) $$map_file; \
	done

test_val_good_map:	all
	@for map_file in ./maps/good/*.cub; do \
		echo "$$map_file"; \
		valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) $$map_file; \
	done

test_wrong_map:	all
	@for map_file in ./maps/wrong/*.cub; do \
		echo "$$map_file"; \
		./$(NAME) $$map_file; \
	done

test_good_map:	all
	@for map_file in ./maps/good/*.cub; do \
		echo "$$map_file"; \
		./$(NAME) $$map_file; \
	done

rerun: re run

gdb:	all
		gdb --args ./$(NAME) $(ARGS)

lldb:	all
		lldb ./$(NAME) $(ARGS)

valgrind: 	all
			valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) $(ARGS)

.PHONY: re all clean fclean debug test $(LIBFT)