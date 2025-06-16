RED    = $(shell printf "\033[31m")
RESET  = $(shell printf "\033[0m")

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = cub3D
RM = rm -rf

LIBFT_DIR = libraries/libft
LIBFT = $(LIBFT_DIR)/libft.a

DIR_OBJ = obj
GETLINE_DIR = libraries/getline
DIR_SRC = mandatory/

SRC_GETLINE = $(GETLINE_DIR)/get_next_line.c 
SRC = $(DIR_SRC)main.c
SRC += $(SRC_GETLINE)

OBJ = $(patsubst $(DIR_SRC)%.c, $(DIR_OBJ)/%.o, $(filter $(DIR_SRC)%,$(SRC))) \
      $(patsubst $(GETLINE_DIR)/%.c, $(DIR_OBJ)/getline/%.o, $(filter $(GETLINE_DIR)/%,$(SRC)))

all: $(DIR_OBJ) $(LIBFT) $(NAME)

$(LIBFT):
	@make --no-print-directory -C $(LIBFT_DIR)
	@make --no-print-directory -C $(LIBFT_DIR) bonus

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

	
$(DIR_OBJ)/%.o: $(DIR_SRC)%.c
	@mkdir -p $(DIR_OBJ)
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
