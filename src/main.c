/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 06:51:00 by aderison          #+#    #+#             */
/*   Updated: 2024/08/06 00:15:40 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>

void	print_path(t_node *end)
{
	t_node	*current;
	char	grid[23][30];
	int		i;
	int		j;

	i = 0;
	while (i < 23)
	{
		j = 0;
		while (j < 31)
		{
			grid[i][j] = '.';
			j++;
		}
		i++;
	}
	current = end;
	while (current)
	{
		grid[current->pos.y][current->pos.x] = '*';
		current = current->parent;
	}
	i = 0;
	while (i < 23)
	{
		j = 0;
		while (j < 31)
		{
			ft_printf("%c ", grid[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	initialize_astar(t_astar *tastar, t_window *window, t_point src,
		t_point dest)
{
	tastar->width = window->col_size;
	tastar->height = window->row_size;
	tastar->start.x = src.x;
	tastar->start.y = src.y;
	tastar->end.x = dest.x;
	tastar->end.y = dest.y;
	tastar->grid = malloc(sizeof(t_node *) * window->row_size);
}

void	fill_grid(t_astar *tastar, t_window *window)
{
	int	i;
	int	j;

	i = 0;
	while (i < window->row_size)
	{
		tastar->grid[i] = malloc(sizeof(t_node) * window->col_size);
		j = 0;
		while (j < window->col_size)
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
	tastar->grid[tastar->start.y][tastar->start.x].g = 0;
	tastar->grid[tastar->start.y][tastar->start.x].f = tastar->grid[tastar->start.y][tastar->start.x].h;
}

int	process_result(t_node *result)
{
	if (result)
	{
		ft_printf("Path found!\n");
		print_path(result);
	}
	else
		ft_printf("No path found.\n");
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (ft_putstr_fd(RED ARG_ERR RESET, 2));
	if (!file_exist(argv[1]) || !file_extention(argv[1], ".ber"))
		return (1);
	init_maps(argv[1], &(game.window));
	if (!syntaxe_error(&game.window) || !is_valid_map(game.window.maps))
		return (ft_printf("error"));
	if (!check_collectible((t_point){1, 1}, &(game.window)))
		return (ft_printf("error ac"));
	window(&game);
	cleanup(&game);
	return (0);
}

/*

 -------------------------------------
|                  .                  |
| /!\ Attention free la list maps /!\ |
|                  .                  |
 -------------------------------------

*/