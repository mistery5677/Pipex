LIBFT_PATH		=	./libraries/libft
LIBFT			=	$(LIBFT_PATH)/libft.a

SOURCES_FILES		=	pipex.c pipex_utils.c

SOURCES_DIR		=	sources

HEADER			=	$(SOURCES_DIR)/pipex.h

SOURCES			=	$(addprefix $(SOURCES_DIR)/, $(SOURCES_FILES))

OBJECTS			= 	$(SOURCES:.c=.o)

NAME			=	pipex_bonus

BONUS_SOURCES_F = pipex_bonus.c pipex_utils_bonus.c

BONUS_HEADER	=	$(SOURCES_DIR)/pipex_bonus.h

BONUS_SOURCES = $(addprefix $(SOURCES_DIR)/, $(BONUS_SOURCES_F))

BONUS_OBJ = $(BONUS_SOURCES:.c=.o)

BONUS_NAME = pipex

CC			=	cc
RM			=	rm -rf

CFLAGS			=	-Wall -Wextra -Werror

.c.o:
				$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all:			$(NAME)

$(NAME):		$(LIBFT) $(OBJECTS) $(HEADER)
				$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) -o $(NAME)

$(LIBFT):
				$(MAKE) -C $(LIBFT_PATH)

clean:
				$(MAKE) -C $(LIBFT_PATH) clean
				$(RM) $(OBJECTS) $(BONUS_OBJ)

fclean:			clean
				$(MAKE) -C $(LIBFT_PATH) fclean
				$(RM) $(NAME)

re:				fclean all

bonus:	$(BONUS_NAME)

$(BONUS_NAME): $(LIBFT) $(BONUS_OBJ) $(BONUS_HEADER)
				$(CC) $(CFLAGS) $(BONUS_OBJ) $(LIBFT) -o $(BONUS_NAME)

.PHONY:			all clean fclean re libft minilibx bonus
