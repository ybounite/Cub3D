RED    = $(shell printf "\033[31m")
RESET  = $(shell printf "\033[0m")

NAME 	= cub3D
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g3
RM 		= rm -rf

MLX =  -lXext -lX11 -lm

LIBFT_DIR	= libraries/libft
LIBFT	= $(LIBFT_DIR)/libft.a

MLX_LB_DIR	= minilibx-linux
MLX_LB	= $(MLX_LB_DIR)/libmlx.a

DIR_OBJ = obj
GETLINE_DIR = libraries/getline
SRC_DIR	= mandatory
DRAW_MAPS_DIR = $(SRC_DIR)/draw_map
MANAGE_PLAYER_DIR = $(SRC_DIR)/manage_player
PARSING_DIR = $(SRC_DIR)/parsing
RAYCASTING_DIR = $(SRC_DIR)/raycasting
SRC_GETLINE = $(GETLINE_DIR)/get_next_line.c 
RENDER_TEXTURE_DIR = $(SRC_DIR)/render_texture

SRC	= $(SRC_DIR)/main.c \
	  $(PARSING_DIR)/check_file_name.c \
	  $(PARSING_DIR)/syntax_error.c \
	  $(PARSING_DIR)/game_parser.c \
	  $(PARSING_DIR)/list_read.c \
	  $(PARSING_DIR)/config_parser.c \
	  $(PARSING_DIR)/validate_textures.c \
	  $(PARSING_DIR)/check_allowed_characters.c\
	  $(PARSING_DIR)/validate_map.c \
	  $(MANAGE_PLAYER_DIR)/player_init.c \
	  $(MANAGE_PLAYER_DIR)/player_control.c \
	  $(DRAW_MAPS_DIR)/map_renderer.c \
	  $(DRAW_MAPS_DIR)/mlx_utils.c \
	  $(DRAW_MAPS_DIR)/minimap.c \
	  $(RAYCASTING_DIR)/mlx_init_data.c \
	  $(RAYCASTING_DIR)/angle_direction.c \
	  $(RAYCASTING_DIR)/collision_check.c \
	  $(RAYCASTING_DIR)/vertical_intersection.c \
	  $(RAYCASTING_DIR)/horizontal_intersection.c \
	  $(RAYCASTING_DIR)/render_background.c \
	  $(RAYCASTING_DIR)/ray_casting.c \
	  $(RENDER_TEXTURE_DIR)/init_textures.c \

SRC += $(SRC_GETLINE)

OBJ = $(patsubst $(SRC_DIR)%.c, $(DIR_OBJ)/%.o, $(filter $(SRC_DIR)%,$(SRC))) \
      $(patsubst $(GETLINE_DIR)/%.c, $(DIR_OBJ)/getline/%.o, $(filter $(GETLINE_DIR)/%,$(SRC)))

all: $(DIR_OBJ) $(LIBFT) $(NAME)

$(LIBFT):
	@make --no-print-directory -C $(LIBFT_DIR)
	@make --no-print-directory -C $(LIBFT_DIR) bonus

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX) $(LIBFT) $(MLX_LB) -o $(NAME)

	
$(DIR_OBJ)/%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(DIR_OBJ)/getline/%.o: $(GETLINE_DIR)/%.c
	@mkdir -p $(DIR_OBJ)/getline
	$(CC) $(CFLAGS) -c $< -o $@

$(DIR_OBJ):
	mkdir -p $(DIR_OBJ)
	mkdir -p $(DIR_OBJ)/getline

clean:
	$(RM) $(OBJ)
	@make -C $(LIBFT_DIR) clean
	@echo "$(RED)┏┓┓ ┏┓┏┓┳┓┏┓┳┓$(RESET)" 
	@echo "$(RED)┃ ┃ ┣ ┣┫┃┃┣ ┃┃$(RESET)" 
	@echo "$(RED)┗┛┗┛┗┛┛┗┛┗┗┛┻┛$(RESET)" 
	@echo

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)
	$(RM) $(DIR_OBJ)

re: fclean all
