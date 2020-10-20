CC = gcc
FLAGS = -Wall -Wextra -Werror -g3 -O3

# PROGRAM name

NAME = lem-in

# PROGRAM src & obj

SRC_DIR = sources
OBJ_DIR = objects

SRC_NAMES = cmp.c \
	init_ants.c \
	init_ants_check.c \
	init_coord_check.c \
	init_data.c \
	init_flags.c \
	init_line_process.c \
	init_links.c \
	init_prepare.c \
	init_rooms.c \
	init_rooms_check.c \
	init_simple_check.c \
	init_utility.c \
	link.c \
	main.c \
	msg.c \
	msg_error.c \
	msg_error_1.c \
	msg_error_2.c \
	msg_error_3.c \
	msg_help.c \
	msg_success.c \
	msg_usage.c \
	node.c \
	output_data.c \
	output_extra.c \
	output_input.c \
	output_line.c \
	output_prepare.c \
	output_short.c \
	output_utility.c \
	path.c \
	process_bhandari.c \
	process_data.c \
	process_dijkstra.c \
	process_mod_graph.c \
	process_prepare.c \
	process_rest_graph.c \
	process_set.c \
	process_utility.c \
	room.c \
	set.c \
	utility.c

OBJ_NAMES = $(SRC_NAMES:.c=.o)

OBJ = $(addprefix $(OBJ_DIR)/, $(OBJ_NAMES))

# PROGRAM headers

INCL_NAMES = lem_in.h lem_in_types.h
INCL_DIR = includes

INCL = $(addprefix $(INCL_DIR)/, $(INCL_NAMES))

# LIBFT

LIB_NAME = libft.a
LIB_DIR = libft
LIB_INCL_DIR = $(addprefix $(LIB_DIR)/, $(INCL_DIR))
LIBFT = $(addprefix $(LIB_DIR)/, $(LIB_NAME))

# RULES

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) -o $@ $(OBJ) $(LIBFT)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(INCL)
	$(CC) -I$(INCL_DIR) -I$(LIB_INCL_DIR) -o $@ -c $< $(FLAGS)

$(LIBFT): $(LIB_DIR)
	make -C $(LIB_DIR)

clean:	
	make -C $(LIB_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(LIBFT)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
