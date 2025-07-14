RED    = $(shell printf "\033[31m")
RESET  = $(shell printf "\033[0m")

NAME 	= cub3D
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g3
RM 		= rm -rf

MLX = -lmlx -lXext -lX11 -lm

LIBFT_DIR	= libraries/libft
LIBFT	= $(LIBFT_DIR)/libft.a

DIR_OBJ = obj
GETLINE_DIR = libraries/getline
SRC_DIR	= mandatory
PARSING_DIR = $(SRC_DIR)/parsing
RAYCASTING_DIR = $(SRC_DIR)/raycasting
SRC_GETLINE = $(GETLINE_DIR)/get_next_line.c 

SRC	= $(SRC_DIR)/main.c \
	  $(PARSING_DIR)/check_file_name.c \
	  $(PARSING_DIR)/syntax_error.c \
	  $(PARSING_DIR)/game_parser.c \
	  $(PARSING_DIR)/list_read.c \
	  $(PARSING_DIR)/config_parser.c \
	  $(PARSING_DIR)/validate_textures.c \
	  $(PARSING_DIR)/check_allowed_characters.c\
	  $(RAYCASTING_DIR)/player_init.c \
	  $(RAYCASTING_DIR)/mlx_init_data.c 

SRC += $(SRC_GETLINE)

OBJ = $(patsubst $(SRC_DIR)%.c, $(DIR_OBJ)/%.o, $(filter $(SRC_DIR)%,$(SRC))) \
      $(patsubst $(GETLINE_DIR)/%.c, $(DIR_OBJ)/getline/%.o, $(filter $(GETLINE_DIR)/%,$(SRC)))

all: $(DIR_OBJ) $(LIBFT) $(NAME)

$(LIBFT):
	@make --no-print-directory -C $(LIBFT_DIR)
	@make --no-print-directory -C $(LIBFT_DIR) bonus

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX) $(LIBFT) -o $(NAME)

	
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