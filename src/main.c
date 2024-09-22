/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 06:51:00 by aderison          #+#    #+#             */
/*   Updated: 2024/09/22 02:26:09 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	initialize_astar(t_astar *tastar, t_window *window, t_point src,
		t_point dest)
{
	tastar->width = window->col_size;
	tastar->height = window->row_size;
	tastar->start.x = src.x;
	tastar->start.y = src.y;
	tastar->end.x = dest.x;
	tastar->end.y = dest.y;
	tastar->grid = NULL;
	tastar->grid = malloc(sizeof(t_node *) * window->row_size);
}

void	fill_grid(t_astar *tastar, t_window *window)
{
	int	i;
	int	j;

	i = 0;
	while (i < tastar->height)
	{
		tastar->grid[i] = malloc(sizeof(t_node) * window->col_size);
		if (!tastar->grid[i])
			return ;
		j = 0;
		while (j < tastar->width)
		{
			tastar->grid[i][j] = *create_node(j, i);
			tastar->grid[i][j].h = heuristic((t_point){j, i}, tastar->end);
			if (window->maps[i][j] == '1')
				tastar->grid[i][j].g = -1;
			else
				tastar->grid[i][j].g = INT_MAX;
			j++;
		}
		i++;
	}
}

void	set_start_node(t_astar *tastar)
{
	int	y;
	int	x;

	x = tastar->start.x;
	y = tastar->start.y;
	tastar->grid[y][x].g = 0;
	tastar->grid[y][x].f = tastar->grid[y][x].h;
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (ft_putstr_fd(RED ARG_ERR RESET, 2));
	if (!file_exist(argv[1]) || !file_extention(argv[1], ".ber"))
		return (1);
	init_maps(argv[1], &(game.window));
	if (!syntaxe_error(&game.window) || !is_valid_map(&game.window))
		return (ft_printf("error"));
	if (!check_collectible((t_point){1, 1}, &(game.window)))
		return (ft_printf("error ac"));
	window(&game);
	cleanup(&game);
	return (0);
}
