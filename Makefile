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

NAME			:= cub3d
UNAME			:= $(shell uname)
CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror

#Libs
LIBFT			= libft/

#Linkers
LINKS			= -L/usr/lib -L$(MLX_DIR) -lXext -lX11 -lm -lz #-lpthread

#Includes
INKS			= -I$(CURDIR) -I$(LIBFT) -I$(MLX_DIR)

ifeq ($(UNAME),Darwin)
	MLX_DIR		= minilibx_opengl
	MLX			= $(MLX_DIR)/libmlx.a
	URL			= https://github.com/42paris/minilibx_opengl
	DEFS		=
	INKS		+= -I/usr/X11/include -I$(MLX_DIR)
	LINKS		+= -I/opt/homebrew/include -I/usr/X11/include -L/usr/X11/lib -framework OpenGL -framework AppKit
else ifeq ($(UNAME),Linux)
	MLX_DIR		= minilibx-linux
	MLX			= $(MLX_DIR)/libmlx_$(UNAME).a
	URL			= https://github.com/42paris/minilibx-linux
	DEFS		=
	INKS		+= -I/usr/include
	LINKS		+= -lmlx_Linux -I$(MLX_DIR)
else
	UNAME = Error
endif

#source files (expected in the root folder)
SRCS_DIR		=
SRC_FILES		= main.c \
				\
				cast_ray.c \
				cast_field.c \
				\
				put_board.c \
				my_pixel_put.c \
				put_line.c \
				put_central_line.c \
				put2d.c \
				\
				parsing.c \
				\
				update_frame.c \
				handle_keys.c handle_mouse.c handle_hover.c \
				clean_exit.c utils.c \
				\
				debug.c

SRCS			= $(addprefix $(SRCS_DIR), $(SRC_FILES))

# Objects
OBJS_DIR		= obj/
OBJ_FILES		= $(SRCS:.c=.o)
OBJS			= $(addprefix $(OBJS_DIR), $(OBJ_FILES))

VPATH 			= rays/ \
				puts/ \
				input/ \
				parsing/ \
				utils/

all: $(NAME)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c | $(OBJS_DIR) 
	$(CC) $(CFLAGS) $(INKS) $(DEFS) -c $< -o $@

test: main.c $(OBJS)
	@echo "${BOLD}compiling $@...${RESET}"
	@$(CC) $(CFLAGS) main.c $(OBJS_DIR)/* $(LINKS) $(INKS) -o $@ \
	&& echo "${LIGHT_GREEN}DONE${RESET}"

$(MLX_DIR):
	@echo "${BOLD}creating $(MLX_DIR)...${RESET}"
	@git clone $(URL) && $(MAKE) -C $(MLX_DIR)

$(MLX): $(MLX_DIR)
	@rm -f $(MLX_DIR)/libmlx.a
	@$(MAKE) -C $(MLX_DIR) --quiet

$(LIBFT)libft.a:
	@echo "${BOLD}compiling libft...${RESET}"
	@$(MAKE) all -C $(LIBFT) --quiet

$(NAME): $(LIBFT)libft.a $(MLX) $(OBJS)
	@echo "${BOLD}compiling the $(NAME)...${RESET}"
	$(CC) $(CFLAGS) $(OBJS_DIR)* $(LIBFT)libft.a $(MLX) -I$(INKS) $(LINKS) -o $(NAME)
	@echo "${LIGHT_GREEN}DONE${RESET}"

tar:
	@ls | grep -q "$(NAME).tar" && rm -f $(NAME).tar || true
	@tar -cf $(NAME).tar --exclude=".git" --exclude="$(NAME)" --exclude="$(OBJS_DIR)" --exclude="$(MLX_DIR)" ./*

clean:
	@rm -f $(OBJS_DIR)* game test
	@$(MAKE) clean -C $(LIBFT) --quiet
fclean: clean
	@rm -rf $(OBJS_DIR)
	@$(MAKE) fclean -C $(LIBFT) --quiet

lre: clean all

re: fclean all