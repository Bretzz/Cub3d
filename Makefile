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
CFLAGS			:= -Wall -Wextra -Werror -g #--std=gnu89

#Libs
LIBFT			= libft/
HPC				= hpc/
YFT				= yft/

#Linkers
LINKS			= -L/usr/lib -L$(MLX_DIR) -lXext -lX11 -lm -lz -lpthread

#Includes
INKS			= -I$(CURDIR) -I$(LIBFT) -I$(MLX_DIR) -I$(HPC)include -I$(YFT)include

ifeq ($(UNAME),Darwin)
	MLX_DIR		= minilibx_opengl
	MLX			= $(MLX_DIR)/libmlx.a
	CLONE		= curl https://cdn.intra.42.fr/document/document/34410/minilibx_macos_opengl.tgz --output $(MLX_DIR).tgz \
				&& tar -xf $(MLX_DIR).tgz && rm -f $(MLX_DIR).tgz \
				&& ls $(MLX_DIR) || mv `ls | grep $(MLX_DIR)` $(MLX_DIR)
	DEFS		= -D __APPLE__
	INKS		+= -I/usr/X11/include
	LINKS		+= -I/opt/homebrew/include -I/usr/X11/include -L/usr/X11/lib -framework OpenGL -framework AppKit
else ifeq ($(UNAME),Linux)
	MLX_DIR		= minilibx-linux
	MLX			= $(MLX_DIR)/libmlx_$(UNAME).a
	CLONE		= git clone https://github.com/42paris/minilibx-linux.git
	DEFS		=
	INKS		+= -I/usr/include
	LINKS		+= -lmlx_Linux
else
	UNAME = Error
endif

#source files (expected in the root folder)
SRCS_DIR		=
SRC_FILES		= main.c \
				\
				cast_ray.c \
				cast_field.c \
				cast_utils.c \
				cast_data.c \
				\
				my_pixel_put.c \
				my_string_put.c \
				my_string_db.c \
				my_number_put.c \
				image_pixel_put.c \
				get_pixel_color.c \
				put_board.c \
				put_line.c \
				put_whole_column.c \
				put2d.c \
				puts_utils.c \
				\
				parsing.c \
				parsing_map.c \
				parsing_utils.c \
				get_player_stats.c \
				get_map_stats.c \
				map_padding.c \
				just_one_player.c \
				\
				update_frame.c get_fps.c \
				move_player.c move_player_dom.c \
				move_mouse.c \
				handle_key_press.c handle_key_release.c \
				handle_mouse.c handle_hover.c \
				clean_exit.c \
				\
				utils.c \
				load_walls_texture.c \
				is_white.c \
				\
				debug.c

SRCS			= $(addprefix $(SRCS_DIR), $(SRC_FILES))

#B_SRCS_DIR		= bonus/
B_SRC_FILES		= main_bonus.c \
				main_data_init.c main_ack_map_init.c \
				clean_exit_bonus.c \
				update_frame_bonus.c \
				\
				move_player_bonus.c move_and_slide_bonus.c \
				move_mouse_bonus.c handle_mouse_bonus.c \
				\
				pos_get_data.c \
				\
				put_board_bonus.c \
				player_handle.c player_put.c \
				put_whole_column_bonus.c \
				\
				put_sprite.c \
				put_sprite_on_map.c \
				put_health_bar.c \
				put_name_tag.c \
				\
				put2d_minimap.c put2d_mini_ray.c \
				put2d_mini_lobby.c \
				put_crosshair.c \
				\
				send_all.c tiny_utils.c \
				sprite_init.c sprite_destroy.c 

# Get the corresponding non-bonus version of bonus files (e.g., parser_bonus.c -> parser.c)
B_REPLACED		= $(patsubst %_bonus.c,%.c,$(filter %_bonus.c,$(B_SRC_FILES)))

# Final bonus source list: SRC_FILES minus the ones replaced, plus the bonus files
BONUS_FILES		= $(filter-out $(B_REPLACED), $(SRC_FILES)) $(B_SRC_FILES)

# If you want full paths using SRCS_DIR:
B_SRCS			= $(addprefix $(SRCS_DIR), $(BONUS_FILES))

# Recompile with -D BONUS
B_RECOMPILE		= input/handle_key_press.c

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

bonus: $(NAME_BONUS)

show_bonus:
	@printf "SCRIPT		: $(SCRIPT)\n"
	@printf "BOBJS		: $(B_OBJS)\n"
	@printf "B_REPLACED		  : $(B_REPLACED:.c=.o)\n"
	@printf "MANDATORY REMOVE : $(addprefix $(OBJS_DIR), $(B_SRC_FILES:.c=.o))\n"

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

#-D DEBUG=1
$(OBJS_DIR)%.o: $(SRCS_DIR)%.c | $(OBJS_DIR) 
	$(CC) $(CFLAGS) $(INKS) $(DEFS) -D DEBUG=1 -c $< -o $@

$(MLX_DIR):
	@echo "${BOLD}creating $(MLX_DIR)...${RESET}"
	$(CLONE) && $(MAKE) -C $(MLX_DIR)

$(MLX): $(MLX_DIR)
	@rm -f $(MLX_DIR)/libmlx.a
	@$(MAKE) -C $(MLX_DIR) --quiet

$(LIBFT)libft.a:
	@echo "${BOLD}compiling libft...${RESET}"
	@$(MAKE) all -C $(LIBFT) --quiet

$(HPC)hpc.a:
	@echo "${BOLD}compiling hpc...${RESET}"
	@$(MAKE) all -C $(HPC) --quiet

$(YFT)yft.a:
	@echo "${BOLD}compiling yft...${RESET}"
	@$(MAKE) all -C $(YFT) --quiet

$(NAME): $(LIBFT)libft.a $(MLX) $(OBJS)
	@rm -rf $(addprefix $(OBJS_DIR), $(B_SRC_FILES:.c=.o))
	@echo "${BOLD}compiling $(NAME)...${RESET}"
	$(CC) $(CFLAGS) $(INKS) $(DEFS) -c $(B_RECOMPILE)
	@mv $(notdir $(B_RECOMPILE:.c=.o)) $(OBJS_DIR)
	@$(CC) $(CFLAGS) $(OBJS_DIR)* $(LIBFT)libft.a $(MLX) -I$(INKS) $(LINKS) -o $(NAME) \
	&& echo "${LIGHT_GREEN}DONE${RESET}"

$(NAME_BONUS): $(YFT)yft.a $(HPC)hpc.a $(LIBFT)libft.a $(MLX) $(B_OBJS)
	@rm -rf $(addprefix $(OBJS_DIR), $(B_REPLACED:.c=.o))
	@echo "${BOLD}compiling $(NAME_BONUS)...${RESET}"
	$(CC) $(CFLAGS) $(INKS) -Ibonus/ $(DEFS) -D BONUS -c $(B_RECOMPILE)
	@mv $(notdir $(B_RECOMPILE:.c=.o)) $(OBJS_DIR)
	@$(CC) $(CFLAGS) -D BONUS $(OBJS_DIR)* $(YFT)yft.a $(HPC)hpc.a $(LIBFT)libft.a $(MLX) -I$(INKS) $(LINKS) -o $(NAME_BONUS) \
	&& echo "${LIGHT_GREEN}DONE${RESET}"

run.sh:
	@> $@ echo '\
	\#!/bin/bash \
	\
	export NAME= SERVER_IP= LOCAL_IP= \
	\
	if [ "$$(uname)" = "Linux" ]; then \
		LOCAL_IP=$$(hostname -i); \
	else \
		LOCAL_IP=$$(ipconfig getifaddr en0); \
	fi \
	\
	./cub3D_bonus $$1 $$2 $$3'
	@sed -i 's/\\//g' $@
	@chmod +x $@

tar:
	@ls | grep -q "$(NAME).tar" && rm -f $(NAME).tar || true
	@tar -cf $(NAME).tar --exclude=".git" --exclude="$(NAME)" --exclude="$(OBJS_DIR)" --exclude="$(MLX_DIR)" ./*

clean:
	@rm -f $(OBJS_DIR)*
	@$(MAKE) clean -C $(LIBFT) --quiet
	@$(MAKE) clean -C $(HPC) --quiet
	@$(MAKE) clean -C $(YFT) --quiet

fclean: clean
	@rm -rf $(OBJS_DIR) $(NAME) $(NAME)_bonus
	@$(MAKE) fclean -C $(LIBFT) --quiet
	@$(MAKE) fclean -C $(HPC) --quiet
	@$(MAKE) fclean -C $(YFT) --quiet

lre: clean all

re: fclean all

.PHONY: all clean fclean re lre bonus
