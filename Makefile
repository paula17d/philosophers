
NAME		=	philo
BONUS_NAME	= 	_bonus

HEADER	=	

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror 
#-O2 -g -fsanitize=thread

SRC_DIR			=	src
OBJ_DIR			=	src_o
SRC_BONUS_DIR	=	src_bonus
OBJ_BONUS_DIR	=	src_bonus_o

SRC_FILES		=	main.c parsing.c init.c routine.c philo_actions.c time.c utils.c death_monitor.c simulation.c print_message.c
SRC_BONUS_FILES	=

SRC			=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ			=	$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
SRC_BONUS	=	$(addprefix $(SRC_BONUS_DIR)/, $(SRC_BONUS_FILES))
OBJ_BONUS	=	$(patsubst $(SRC_BONUS_DIR)/%.c, $(OBJ_BONUS_DIR)/%.o, $(SRC_BONUS))


$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

%.o: %.c $(HEADER)
	@$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

clean:
	@rm -rf $(OBJ_DIR) $(OBJ_BONUS_DIR)

fclean: clean
	@rm -rf $(NAME) $(BONUS_NAME)
	@rm -rf screenshot.bmp

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean fclean re bonus
