# define standard colors
BOLD			= \033[1m
BLACK    		= \033[30m    # Black
RED      		= \033[31m    # Red
GREEN    		= \033[32m    # Green
YELLOW   		= \033[33m    # Yellow
BLUE     		= \033[34m    # Blue
MAGENTA  		= \033[35m    # Magenta
CYAN     		= \033[36m    # Cyan
WHITE    		= \033[37m    # White
LIGHT_RED		= \033[91m
LIGHT_GREEN		= \033[92m
LIGHT_CYAN		= \033[96m
RESET			= \033[0m

NAME			= libft.a
CC				= cc
CFLAGS			= -Wall -Wextra -Werror

#source files (full path optional)
SRCS_DIR		=
SRC_FILES		= ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
				ft_isdigit.c ft_isprint.c ft_isspace.c ft_itoa.c ft_split.c ft_memchr.c ft_memcmp.c \
				ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
				ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c \
				ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
				ft_strchr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
				\
				ft_lstadd_back.c ft_lstadd_front.c \
				ft_lstclear.c ft_lstdelone.c ft_lstnew.c \
				ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstsize.c \
				\
				ft_printf.c \
				nest_putexa_fd.c \
				nest_putptr_fd.c \
				nest_putput_fd.c \
				nest_putuns_fd.c \
				nest_putztr_fd.c \
				nest_putflo_fd.c \
				west_putchar_fd.c \
				west_putnbr_fd.c \
				west_putstr_fd.c \
				\
				get_next_line.c \
				get_next_line_utils.c \
				\
				ft_atof.c ft_atohexi.c \
				ft_strichr.c ft_strcmp.c \
				ft_realloc.c \
				\
				ft_dropstr.c ft_strjoin_free.c \
				ft_chrnum.c \
				\
				ft_mtxlen.c free_mtx.c


SRCS			= $(addprefix $(SRCS_DIR), $(SRC_FILES))


#folders containing source files [*.c]
VPATH			= printf/ \
					get_next_line/

#Includes
INK				= -I$(CURDIR)

# Objects
OBJS_DIR		= obj/
OBJ_FILES		= $(SRCS:.c=.o)
OBJS			= $(addprefix $(OBJS_DIR), $(OBJ_FILES))
GIDEF			=	"""$\
					\#default rules\n$\
					.gitignore\n$\
					.git\n$\
					.vscode\n$\
					**/temp\n$\
					**/$(OBJS_DIR)\n$\
					**/resources\n$\
					**/a.out\n$\
					**/*.a\n$\
					**/tester.c\n$\
					\n$\
					\#added rules\n$\
					"""

all: $(NAME)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c | $(OBJS_DIR) 
	$(CC) $(CFLAGS) $(INK) $(DEFS) -c $< -o $@

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS_DIR)*

.gitignore:
	@touch .gitignore
	@cat .gitignore | grep "#default rules" || \
		echo $(GIDEF)"$$(cat .gitignore)" > .gitignore

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re main .gitignore
