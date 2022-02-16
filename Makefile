# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tnard <tnard@student.42lyon.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/08 16:54:23 by tnard             #+#    #+#              #
#    Updated: 2022/02/16 11:03:28 by tnard            ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

BLU			= \033[0;34m
GRN			= \033[0;32m
RED			= \033[0;31m
RST			= \033[0m
END			= \e[0m

SOURCES	= server.c client.c
OBJECTS	= $(SOURCES:.c=.o)
NAME	= minitalk
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

all: server client

bonus: server client

server: server.o libft
	@$(CC) -o $@ $< -Llibft -lft

client: client.o libft
	@$(CC) -o $@ $< -Llibft -lft
	@printf "\033[2K\r\033[0;32m[END]\033[0m $(NAME)\n"

%.o: %.c
	@$(CC) -c $(CFLAGS) $?
	@printf	"\033[2K\r${BLU}[BUILD - $(NAME)]${RST} '$<' $(END)"

libft:
	@make -C libft

clean:
	@rm -f $(OBJECTS)
	@make -C libft clean
	
fclean: clean
	@rm -f server client libft/libft.a

re: fclean all

.PHONY: all bonus libft clean fclean re