RED    = $(shell printf "\33[31m")

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = cub3D
RM = mr -rf
DIR_OBJ = obj/
DIR_SRC = mandatoryc/

SRC = $(DIR_SRC)main.c

OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ)
	@echo "$(RED)┏┓┓ ┏┓┏┓┳┓┏┓┳┓" 
	@echo "┃ ┃ ┣ ┣┫┃┃┣ ┃┃" 
	@echo "┗┛┗┛┗┛┛┗┛┗┗┛┻┛" 
	@echo

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(OBJ_DIR)

re: fclean all