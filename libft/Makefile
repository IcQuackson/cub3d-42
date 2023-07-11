
NAME = libft.a

SRC = ft_memset ft_bzero ft_memcpy ft_memmove ft_memchr\
ft_memcmp ft_strlen ft_strchr ft_strrchr ft_atoi ft_strlcpy\
ft_strnstr ft_strncmp ft_strcmp ft_isalpha ft_isdigit ft_isalnum\
ft_isascii ft_isprint ft_toupper ft_tolower ft_strlcat\
ft_calloc ft_strdup ft_strjoin ft_strtrim ft_substr\
ft_split ft_itoa ft_strmapi ft_striteri ft_putchar_fd\
ft_putnbr_fd ft_putstr_fd ft_putendl_fd\

BONUS = ft_lstnew ft_lstadd_front ft_lstsize ft_lstlast ft_lstadd_back\
ft_lstdelone ft_lstclear ft_lstiter ft_lstmap\

CC = gcc
RM = rm -f
CFLAGS = -Wall -Werror -Wextra -g
AR	= ar rcs

OBJSF		=	.cache_exists

all:		$(NAME) bonus

$(NAME): $(SRC:=.o)
			@$(AR) $(NAME) $(SRC:=.o)

bonus:	$(BONUS:=.o)
			@$(AR) $(NAME) $(BONUS:=.o)

clean:
			@$(RM)	$(SRC:=.o) $(BONUS:=.o)

fclean:		clean
			@$(RM) -f $(NAME)

re:			fclean all

norm:
	@norminette $(SRCS) $(INCLUDES) | grep -v Norme -B1 || true

.PHONY:		all bonus clean fclean re norm