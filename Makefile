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

NAME			:= cub3D
NAME_BONUS		:= $(NAME)_bonus
UNAME			:= $(shell uname)
CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror

#Libs
LIBFT			= libft/
#HPC				= hpc/

#Linkers
LINKS			= -L/usr/lib -L$(MLX_DIR) -lXext -lX11 -lm -lz #-lpthread

#Includes
INKS			= -I$(CURDIR) -I$(LIBFT) -I$(MLX_DIR) #-I$(HPC)include

ifeq ($(UNAME),Darwin)
	MLX_DIR		= minilibx_opengl
	MLX			= $(MLX_DIR)/libmlx.a
	CLONE		= curl https://cdn.intra.42.fr/document/document/34410/minilibx_macos_opengl.tgz --output $(MLX_DIR).tgz \
				&& tar -xf $(MLX_DIR).tgz && rm -f $(MLX_DIR).tgz \
				&& ls $(MLX_DIR) || mv `ls | grep $(MLX_DIR)` $(MLX_DIR)
	DEFS		= -D __APPLE__
	INKS		+= -I/usr/X11/include -I$(MLX_DIR)
	LINKS		+= -I/opt/homebrew/include -I/usr/X11/include -L/usr/X11/lib -framework OpenGL -framework AppKit
else ifeq ($(UNAME),Linux)
	MLX_DIR		= minilibx-linux
	MLX			= $(MLX_DIR)/libmlx_$(UNAME).a
	CLONE		= git clone https://github.com/42paris/minilibx-linux.git
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
				my_pixel_put.c \
				get_pixel_color.c \
				put_board.c \
				put_line.c \
				put_whole_column.c \
				put2d.c \
				\
				parsing.c \
				get_player_stats.c \
				get_map_stats.c \
				\
				update_frame.c \
				move_player.c move_player_dom.c \
				move_mouse.c \
				handle_keys.c handle_mouse.c handle_hover.c \
				clean_exit.c utils.c \
				\
				debug.c

SRCS			= $(addprefix $(SRCS_DIR), $(SRC_FILES))

#B_SRCS_DIR		= bonus/
B_SRC_FILES		= main_bonus.c clean_exit_bonus.c \
				move_player_bonus.c move_mouse_bonus.c \
				put_board_bonus.c \
				put_whole_column_bonus.c \
				put_sprite_on_map.c put_player.c

# Get the corresponding non-bonus version of bonus files (e.g., parser_bonus.c -> parser.c)
B_REPLACED		= $(patsubst %_bonus.c,%.c,$(filter %_bonus.c,$(B_SRC_FILES)))

# Final bonus source list: SRC_FILES minus the ones replaced, plus the bonus files
BONUS_FILES		= $(filter-out $(B_REPLACED), $(SRC_FILES)) $(B_SRC_FILES)

# If you want full paths using SRCS_DIR:
B_SRCS			= $(addprefix $(SRCS_DIR), $(BONUS_FILES))

# Objects
OBJS_DIR		= obj/
OBJ_FILES		= $(SRCS:.c=.o)
OBJS			= $(addprefix $(OBJS_DIR), $(OBJ_FILES))

#Bonus objects
B_OBJ_FILES		= $(B_SRCS:.c=.o)
B_OBJS			= $(addprefix $(OBJS_DIR), $(B_OBJ_FILES))

VPATH 			= rays \
				puts \
				input \
				parsing \
				utils \
				bonus

all: $(NAME)

show_bonus:
	@printf "BOBJS		: $(B_OBJS)\n"
	@printf "B_REPLACED		  : $(B_REPLACED:.c=.o)\n"
	@printf "MANDATORY REMOVE : $(addprefix $(OBJS_DIR), $(B_SRC_FILES:.c=.o))\n"

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)


$(OBJS_DIR)%.o: $(SRCS_DIR)%.c | $(OBJS_DIR) 
	$(CC) $(CFLAGS) $(INKS) $(DEFS) -c $< -o $@

#$(OBJS_DIR)%.o: $(SRCS_DIR)%.c | $(OBJS_DIR) 
#	@if echo $< | grep -q "bonus"; then \
		echo "Compiling BONUS: $<"; \
		$(CC) $(CFLAGS) $(INKS) $(DEFS) -D BONUS -c $< -o $@; \
	else \
		echo "Compiling: $<"; \
		$(CC) $(CFLAGS) $(INKS) $(DEFS) -c $< -o $@; \
	fi

$(MLX_DIR):
	@echo "${BOLD}creating $(MLX_DIR)...${RESET}"
	$(CLONE) && $(MAKE) -C $(MLX_DIR)

$(MLX): $(MLX_DIR)
#	@echo ciao
	@rm -f $(MLX_DIR)/libmlx.a
	@$(MAKE) -C $(MLX_DIR) --quiet

$(LIBFT)libft.a:
	@echo "${BOLD}compiling libft...${RESET}"
	@$(MAKE) all -C $(LIBFT) --quiet

#$(HPC)hpc.a:
#	@echo "${BOLD}compiling hpc...${RESET}"
#	@$(MAKE) all -C $(HPC) --quiet

$(NAME): $(LIBFT)libft.a $(MLX) $(OBJS)
	@rm -rf $(addprefix $(OBJS_DIR), $(B_SRC_FILES:.c=.o));
	@echo "${BOLD}compiling $(NAME)...${RESET}"
	@$(CC) $(CFLAGS) $(OBJS_DIR)* $(LIBFT)libft.a $(MLX) -I$(INKS) $(LINKS) -o $(NAME) \
	&& echo "${LIGHT_GREEN}DONE${RESET}"

$(NAME_BONUS): $(LIBFT)libft.a $(MLX) $(B_OBJS)
	@rm -rf $(addprefix $(OBJS_DIR), $(B_REPLACED:.c=.o));
	@echo "${BOLD}compiling $(NAME_BONUS)...${RESET}"
	@$(CC) $(CFLAGS) -D BONUS $(OBJS_DIR)* $(LIBFT)libft.a $(MLX) -I$(INKS) $(LINKS) -o $(NAME_BONUS) \
	&& echo "${LIGHT_GREEN}DONE${RESET}"

bonus: $(NAME_BONUS)

tar:
	@ls | grep -q "$(NAME).tar" && rm -f $(NAME).tar || true
	@tar -cf $(NAME).tar --exclude=".git" --exclude="$(NAME)" --exclude="$(OBJS_DIR)" --exclude="$(MLX_DIR)" ./*

clean:
	@rm -f $(OBJS_DIR)*
	@$(MAKE) clean -C $(LIBFT) --quiet
#	@$(MAKE) clean -C $(HPC) --quiet

fclean: clean
	@rm -rf $(OBJS_DIR) $(NAME) $(NAME)_bonus
	@$(MAKE) fclean -C $(LIBFT) --quiet
#	@$(MAKE) fclean -C $(HPC) --quiet

lre: clean all

re: fclean all

.PHONY: all clean fclean re lre bonus
