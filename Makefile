# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aderison <aderison@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/17 06:35:03 by aderison          #+#    #+#              #
#    Updated: 2024/07/17 08:02:32 by aderison         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Variable general
NAME = so_long
CC = gcc
CFLAGS = -Wall -Wextra -Werror
I_LIBFT = lib/libft/include/
I_MINILIBX = lib/minilibx/
INCLUDES = -Iinclude/ -I$(I_LIBFT) -I$(I_MINILIBX)

# Colors
RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[1;33m
CYAN=\033[0;36m
NC=\033[0m

#push_swap main
SO_LONG_MAIN = main.c 

# so_long sources
SO_LONG_SRCS = $(addprefix src/, $(SO_LONG_MAIN))
SO_LONG_OBJS = $(SO_LONG_SRCS:src/%.c=obj/%.o)


# Compilation rules
all: $(NAME)

$(NAME): $(SO_LONG_OBJS)
	@mkdir -p $(dir $@)
	@make -C lib/libft/
	@make -C lib/minilibx/
	@$(CC) $(CFLAGS) $(INCLUDES) $^ -Llib/minilibx/ -lmlx -Llib/libft/ -lft \
	-framework OpenGL -framework AppKit -o $@
	@echo "${YELLOW}Executable $(NAME) created.${NC}"

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	@echo "\r${CYAN}Compiling $<...${NC}"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	
clean:
	@rm -rf obj
	@echo "${GREEN}Object files cleaned.${NC}"

fclean: clean
	@make fclean -C lib/libft/
	@make clean -C lib/minilibx/
	@rm -f $(NAME)
	@echo "${RED}All files removed.${NC}"

re: fclean all

.PHONY: all clean fclean re
