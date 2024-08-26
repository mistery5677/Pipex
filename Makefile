LIBFT_PATH		=	./libraries/libft
LIBFT			=	$(LIBFT_PATH)/libft.a

SOURCES_FILES		=	pipex.c

SOURCES_DIR		=	sources

HEADER			=	$(SOURCES_DIR)/pipex.h

SOURCES			=	$(addprefix $(SOURCES_DIR)/, $(SOURCES_FILES))

OBJECTS			= 	$(SOURCES:.c=.o)

NAME			=	pipex

CC			=	cc
RM			=	rm -rf

CFLAGS			=	-Wall -Wextra -Werror

.c.o:
				$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all:			$(NAME)

$(NAME):		$(LIBFT) $(OBJECTS) $(HEADER)
				$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) $(MINILIBX) $(MLXFLAGS) -o $(NAME)

$(LIBFT):
				$(MAKE) -C $(LIBFT_PATH)

clean:
				$(MAKE) -C $(LIBFT_PATH) clean
				$(RM) $(OBJECTS)

fclean:			clean
				$(MAKE) -C $(LIBFT_PATH) fclean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re libft minilibx bonus
