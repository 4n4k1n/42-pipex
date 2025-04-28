# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/27 22:42:18 by apregitz          #+#    #+#              #
#    Updated: 2025/04/28 15:00:35 by apregitz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
LIBFT = libft/libft.a

CC = cc
CFLAGS = -Werror

SRC_DIR = src
OBJ_DIR = obj

SRCS = pipex.c \
	parsing.c \
	utils.c

OBJS := $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(LIBFT):
	@echo "Building libft..."
	$(MAKE) -C libft

$(NAME): $(OBJ_DIR) $(OBJS) $(LIBFT)
	@echo "Building $(NAME)..."
	$(CC) $(OBJS) $(LIBFT) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@echo "Creating object directory..."
	mkdir -p $(OBJ_DIR)

clean:
	$(MAKE) -C libft clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re