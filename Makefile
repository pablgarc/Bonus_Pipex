# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pablo <pablo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/12 09:12:24 by pablgarc          #+#    #+#              #
#    Updated: 2024/09/26 22:57:43 by pablo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
NAME_BONUS = pipex_bonus

OBJ_PATH = obj
SRC_PATH = src
INC_PATH = include
LIBFT_PATH = libft
BONUS_PATH = src_bonus

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

SRCS = $(wildcard $(SRC_PATH)/*.c)
OBJS = $(patsubst $(SRC_PATH)/%.c, $(OBJ_PATH)/%.o, $(SRCS))

SRCS_BONUS = $(wildcard $(BONUS_PATH)/*.c)
OBJS_BONUS = $(patsubst $(BONUS_PATH)/%.c, $(OBJ_PATH)/%.o, $(SRCS_BONUS))

all: libft $(NAME)

bonus: libft $(NAME_BONUS)

libft:
	@make -C $(LIBFT_PATH)

clean:
	$(RM) $(OBJ_PATH)
	make clean -C $(LIBFT_PATH)
	

fclean: clean
	make fclean -C $(LIBFT_PATH)
	$(RM) pipex pipex_bonus
	

re: fclean all

rebonus: fclean bonus

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFT_PATH)/libft.a
	

$(NAME_BONUS): $(OBJS_BONUS)
	$(CC) $(CFLAGS) -o $@ $(OBJS_BONUS) $(LIBFT_PATH)/libft.a
	

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(INC_PATH)/pipex.h
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -I $(INC_PATH) -c $< -o $@

$(OBJ_PATH)/%.o: $(BONUS_PATH)/%.c $(INC_PATH)/pipex_bonus.h
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -I $(INC_PATH) -c $< -o $@

.PHONY: all bonus libft clean fclean re rebonus
