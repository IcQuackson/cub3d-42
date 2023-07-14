SRC	= srcs/main.c srcs/map_parser.c srcs/hooks.c srcs/textures_parser.c gnl/get_next_line.c srcs/data_parser.c
BIN	= bin
DEBUGBIN = dbin
INCS	= includes/
#TRIGGER_HEADERS = $(INCS)/test.h
LIBFT	= libft/# Libft folder
LIBFT_INCS = includes/# Libft includes/ folder
LFLAGS	= -L${LIBFT} -lft -Iminilibx-linux -Lminilibx-linux -lmlx -lmlx_Linux -L/usr/lib -lXext -lX11 -lm
CFLAGS	= -Wall -Werror -Wextra -g# -fsanitize=address
DEBUG	=	-D DEBUG
IFLAGS	= -I${INCS} -I${LIBFT_INCS}
UNAME	:= ${shell uname}
NAME	= cub3D
DNAME = debug_test_executable
RM	= rm -rf
OBJS	= ${SRC:srcs/%c=${BIN}/%o}
DOBJS = ${SRC:srcs/%c=${DEBUGBIN}/%o}
VALGRIN_DFLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose
VALGRIND_OUTFILE = valgrind-out.txt

ifeq ($(UNAME), Darwin)
	CC = gcc
else ifeq ($(UNAME), FreeBSD)
	CC = clang
else
	CC	= gcc
	CFLAGS += -D LINUX
endif

all: ${NAME}

${NAME}: ${BIN} ${OBJS} | ${LIBFT}
	${CC} -o ${NAME} ${OBJS} ${LFLAGS}

debug: ${DNAME}

${DNAME}: ${DEBUGBIN} ${DOBJS} | ${LIBFT}
	${CC} -o ${DNAME} ${DOBJS} ${DEBUG} ${LFLAGS}

${BIN}/%o: srcs/%c
	cd minilibx-linux && make
	${CC} -c $< ${CFLAGS} ${IFLAGS} -o $@

${DEBUGBIN}/%o: srcs/%c
	${CC} -c $< ${CFLAGS} ${IFLAGS} ${DEBUG} -o $@

${BIN}:
	@mkdir -p ${BIN}

${DEBUGBIN}:
	@mkdir -p ${DEBUGBIN}

clean:
	cd libft && make clean
	cd minilibx-linux && make clean
	${RM} ${BIN} ${DEBUGBIN}

fclean: clean
		cd libft && make fclean
		${RM} ${NAME} ${DNAME}

run: all
	 ./$(NAME)

gdb:	all
		gdb $(NAME)

valgrind: 	all
			valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

${LIBFT}:
	@make all -C ${LIBFT} --no-print-directory

re: fclean all

test: debug
	@echo "[MAKEFILE] You can setup test arguments by setting up the env FT_LS_ARGS"
	@echo "[MAKEFILE] Ex: export FT_LS_ARGS=\"-a --recursive ..\""
	valgrind ${VALGRIND_FLAGS} --log-file=$(VALGRIND_OUTFILE) ./${DNAME} ${FT_LS_ARGS}

show:
	@printf "UNAME		: ${UNAME}\n"
	@printf "NAME		: ${NAME}\n"
	@printf "CC			: ${CC}\n"
	@printf "CFLAGS		: ${CFLAGS}\n"
	@printf "LFLAGS		: ${LFLAGS}\n"
	@printf "SRC		: ${SRC}\n"
	@printf "OBJS		: ${OBJS}\n"

.PHONY: re all clean fclean debug test ${LIBFT}