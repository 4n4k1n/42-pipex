# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apregitz <apregitz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/27 22:42:18 by apregitz          #+#    #+#              #
#    Updated: 2025/05/10 12:27:47 by apregitz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
LIBFT = libft/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
# SANITIZE = -fsanitize=address,undefined

SRC_DIR = src
OBJ_DIR = obj

SRCS = pipex.c \
	parsing.c \
	utils.c \
	here_doc.c \
	init.c

OBJS := $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(LIBFT):
	$(MAKE) -C libft

$(NAME): $(OBJ_DIR) $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

bonus:
	@$(MAKE) all CFLAGS="$(CFLAGS) -D BONUS=1"

clean:
	$(MAKE) -C libft clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C libft fclean
	rm -f $(NAME)

bre: fclean bonus

re: fclean all

.PHONY: all clean fclean re bonus bre