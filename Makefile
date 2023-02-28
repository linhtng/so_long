# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thuynguy <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/22 15:30:29 by thuynguy          #+#    #+#              #
#    Updated: 2022/11/22 15:30:31 by thuynguy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

CFLAGS = -Wall -Wextra -Werror -g3

LINKS = -lmlx -framework OpenGL -framework AppKit

SRC = so_long_main.c \
	so_long_utils.c \
	so_long_valid_path.c \
	so_long_valid_path_utils.c \
	so_long_valid_map.c \
	so_long_game.c \
	so_long_game_keys.c \
	so_long_game_utils.c

OBJSFD 	= objs

OBJS 	= $(addprefix $(OBJSFD)/,$(SRC:.c=.o))

HDR 		= -I./includes

FT_PRINTF_HDR 	= -I./includes/ft_printf

FT_PRINTF_BINARY	= -L./includes/ft_printf -lftprintf

FT_PRINTF		= ./includes/ft_printf/libftprintf.a

all: $(FT_PRINTF) ./includes/ft_printf/libftprintf.a $(NAME)

FT_PRINTF		= ./includes/ft_printf/libftprintf.a

$(FT_PRINTF):
			make -C ./includes/ft_printf

$(OBJSFD):
	mkdir $@

$(OBJSFD)/%.o: %.c | $(OBJSFD)
	gcc -g $(CFLAGS) $(HDR) $(FT_PRINTF_HDR) -c $< -o $@

$(NAME): $(OBJS) $(FT_PRINTF) ./includes/so_long.h
	gcc -g $(OBJS) $(FT_PRINTF_BINARY) $(LINKS) -o $@

clean:
	rm -f $(OBJS)
	rm -rf $(OBJSFD)
	make -C ./includes/ft_printf clean

fclean: clean
	rm -f $(NAME)
	make -C ./includes/ft_printf fclean

re: fclean all

.PHONY: all clean fclean re
