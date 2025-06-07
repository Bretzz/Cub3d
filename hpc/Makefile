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

NAME			:= hpc.a
UNAME			:= $(shell uname)
CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror

#adds stuff inside the outer libft
LIBFT			= $(shell find .. -type d -name "libft")/

#Libs
MSG				= msg/
LBB				= lbb/

#Linkers
LINKS			=

#Includes
INKS			= -I$(CURDIR) -I$(LIBFT) -Ionline/ -Imsg/ -Iinclude

#source files (expected in the root folder)
SRCS_DIR		=
SRC_FILES		= \
				lbb_data_length.c \
				lbb_get_data.c \
				lbb_init.c \
				lbb_mutex.c \
				lbb_read_data.c \
				lbb_write_data.c \
				lbb_to_msg.c \
				lbb_delete_lobby.c \
				\
				msg_data_length.c \
				msg_get_data.c \
				msg_get_pos_tar.c \
				msg_read_data.c \
				msg_utils.c \
				\
				get_me_online.c \
				get_me_manager.c \
				hpc_free.c \
				hpc_init.c \
				hpc_mutex.c \
				\
				client.c \
				client_reciever.c \
				client_sender.c \
				\
				server.c\
				server_reciever.c \
				server_sender.c \
				\
				actions_game.c actions_online.c \
				buffer_actions.c \
				msg_handler.c \
				\
				convert_stuff.c \
				ft_perror.c \
				fake_env.c search_env.c \
				utils.c get_my_addr.c \
				\
				printers.c

SRCS			= $(addprefix $(SRCS_DIR), $(SRC_FILES))

# Objects
OBJS_DIR		= obj/
OBJ_FILES		= $(SRCS:.c=.o)
OBJS			= $(addprefix $(OBJS_DIR), $(OBJ_FILES))

VPATH 			= $(MSG) $(LBB) \
				online/ \
				online/client/ online/server \
				utils/

all: $(NAME)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c | $(OBJS_DIR) 
	$(CC) $(CFLAGS) $(INKS) $(DEFS) -c $< -o $@

$(LIBFT)libft.a:
	@$(MAKE) all -C $(LIBFT) --quiet

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
#	@ar rcs $(LIBFT)libft.a $(LIBFT)$(OBJS_DIR)* $(OBJS_DIR)*

tar:
	@ls | grep -q "$(NAME).tar" && rm -f $(NAME).tar || true
	@tar -cf $(NAME).tar --exclude=".git" --exclude="$(NAME)" --exclude="$(OBJS_DIR)" --exclude="$(MLX_DIR)" ./*

clean:
	@rm -f $(OBJS_DIR)*

fclean: clean
	@rm -rf $(OBJS_DIR) $(NAME)

lre: clean all

re: fclean all