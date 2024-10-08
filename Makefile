# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aderison <aderison@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/17 06:35:03 by aderison          #+#    #+#              #
#    Updated: 2024/09/22 02:30:40 by aderison         ###   ########.fr        #
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

#so_long utils
SO_LONGS_FILE = $(addprefix file/, file_exist.c file_extention.c)
SO_LONGS_MAPS = $(addprefix maps/, line_checkchr.c line_checknbr.c init.c \
syntaxe_error.c is_valid_map.c astar_utils.c)
SO_LONGS_VIEW = $(addprefix view/, images.c draw_map.c window.c collision.c end_game.c move_ghost.c direction_pac.c game_loop.c use_portal.c)
SO_LONGS_UTILS = $(addprefix utils/, $(SO_LONGS_FILE) $(SO_LONGS_MAPS) $(SO_LONGS_VIEW) ft_snprintf.c)

#so_long maps
SO_LONG_MAPS_F = $(addprefix maps/, astar.c)

#so_long main
SO_LONG_MAIN = main.c 

#so_long sources
SO_LONG_SRCS = $(addprefix src/, $(SO_LONG_MAIN) $(SO_LONGS_UTILS) $(SO_LONG_MAPS_F))
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
	@make -C lib/libft/
	@make -C lib/minilibx/
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
