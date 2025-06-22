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

NAME			:= yft.a
UNAME			:= $(shell uname)
CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror

#adds stuff inside the outer libft
LIBFT			= $(shell find .. -type d -name "libft")
MLX_DIR			= $(shell find .. -type d -name "minilibx*")

#Linkers
LINKS			=

#Includes
INKS			= -I$(CURDIR) -I$(LIBFT) -I$(MLX_DIR)


#source files (expected in the root folder)
SRCS_DIR		=
SRC_FILES		= yft_is_better.c \
				yft_string_to_image.c \
				yft_string_put.c \
				\
				yft_draw_ascii.c \
				yft_fill_font.c \
				yft_fill_map.c \
				yft_img_init.c \
				yft_monoline_file.c \
				yft_parse_file.c \
				yft_read_file.c \
				yft_strip_comments.c \
				\
				img_get_data.c \
				fill_spacing.c

SRCS			= $(addprefix $(SRCS_DIR), $(SRC_FILES))

# Objects
OBJS_DIR		= obj/
OBJ_FILES		= $(SRCS:.c=.o)
OBJS			= $(addprefix $(OBJS_DIR), $(OBJ_FILES))

VPATH 			= 

all: $(NAME)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

#-D DEBUG=1
$(OBJS_DIR)%.o: $(SRCS_DIR)%.c | $(OBJS_DIR) 
	$(CC) $(CFLAGS) $(INKS) $(DEFS) -c $< -o $@

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)

tar:
	@ls | grep -q "$(NAME).tar" && rm -f $(NAME).tar || true
	@tar -cf $(NAME).tar --exclude=".git" --exclude="$(NAME)" --exclude="$(OBJS_DIR)" --exclude="$(MLX_DIR)" ./*

clean:
	@rm -f $(OBJS_DIR)*

fclean: clean
	@rm -rf $(OBJS_DIR) $(NAME)

lre: clean all

re: fclean all

.PHONY: all clean fclean re lre tar