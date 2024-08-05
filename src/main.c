/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 06:51:00 by aderison          #+#    #+#             */
/*   Updated: 2024/08/05 07:53:45 by aderison         ###   ########.fr       */
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

void	load_images(t_game *game)
{
	int	img_width;
	int	img_height;

	img_width = 32;
	img_height = 32;
	game->images.wall = mlx_xpm_file_to_image(game->window.mlx,
			"./assets/xpm/wall.xpm", &img_width, &img_height);
	game->images.collectible = mlx_xpm_file_to_image(game->window.mlx,
			"./assets/xpm/food.xpm", &img_width, &img_height);
	game->images.ghost = mlx_xpm_file_to_image(game->window.mlx,
			"./assets/xpm/ghost.xpm", &img_width, &img_height);
	game->images.background = mlx_xpm_file_to_image(game->window.mlx,
			"./assets/xpm/black.xpm", &img_width, &img_height);
}

void	cleanup(t_game *game)
{
	int	i;

	if (game->images.wall)
		mlx_destroy_image(game->window.mlx, game->images.wall);
	if (game->images.collectible)
		mlx_destroy_image(game->window.mlx, game->images.collectible);
	if (game->images.player)
		mlx_destroy_image(game->window.mlx, game->images.player);
	if (game->images.exit)
		mlx_destroy_image(game->window.mlx, game->images.exit);
	if (game->images.ghost)
		mlx_destroy_image(game->window.mlx, game->images.ghost);
	if (game->window.win)
		mlx_destroy_window(game->window.mlx, game->window.win);
	if (game->window.mlx)
	{
		mlx_destroy_window(game->window.mlx, game->window.win);
		ft_free(1, &game->window.mlx);
	}
	i = -1;
	while (++i < game->window.row_size)
		ft_free(1, &game->window.maps[i]);
	ft_free(1, &game->window.maps);
}

int	close_window(t_game *game)
{
	cleanup(game);
	exit(0);
}

void	draw_map(t_game *game)
{
	int		y;
	int		x;
	void	*img_to_use;

	y = 0;
	while (y < game->window.row_size)
	{
		x = 0;
		while (x < game->window.col_size)
		{
			img_to_use = NULL;
			if (game->window.maps[y][x] == '1')
				img_to_use = game->images.wall;
			else if (game->window.maps[y][x] == 'C')
				img_to_use = game->images.collectible;
			else if (game->window.maps[y][x] == 'G')
				img_to_use = game->images.ghost;
			else if (game->window.maps[y][x] == '0')
				img_to_use = game->images.background;
			if (img_to_use)
				mlx_put_image_to_window(game->window.mlx, game->window.win,
					img_to_use, x * 32, y * 32);
			x++;
		}
		y++;
	}
}

void	init_ghost(t_game *game)
{
	game->ghost.x = 1;
	game->ghost.y = 1;
	game->ghost.dx = 1;
	game->ghost.dy = 0;
	game->ghost.path = NULL;
	game->ghost.path_index = -1;
}
t_point	find_target(void)
{
	t_point	target;

	target.x = 13;
	target.y = 13;
	return (target);
}
void	move_ghost(t_game *game)
{
	t_point	target;
	t_astar	tastar;
	t_point	start;
	t_node	*result;
	t_node	*next_move;

	target = find_target();
	start = (t_point){game->ghost.x, game->ghost.y};
	initialize_astar(&tastar, &game->window, start, target);
	fill_grid(&tastar, &game->window);
	set_start_node(&tastar);
	result = astar(&tastar);
	if (result && result->parent)
	{
		// Trouver le prochain mouvement
		next_move = result;
		while (next_move->parent && next_move->parent->parent)
		{
			next_move = next_move->parent;
		}
		// Déplacer le fantôme
		game->window.maps[game->ghost.y][game->ghost.x] = '0';
		game->ghost.x = next_move->pos.x;
		game->ghost.y = next_move->pos.y;
		game->window.maps[game->ghost.y][game->ghost.x] = 'G';
	}
	// Nettoyer la mémoire allouée par A*
	free_grid(&tastar);
}

int	update_game(t_game *game)
{
	static int	frame_count = 0;

	frame_count++;
	if (frame_count % 30 == 0) // Déplacez le fantôme toutes les 30 frames
	{
		move_ghost(game);
		draw_map(game);
	}
	draw_map(game);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	window;

	if (argc != 2)
		return (ft_putstr_fd(RED ARG_ERR RESET, 2));
	if (!file_exist(argv[1]) || !file_extention(argv[1], ".ber"))
		return (1);
	init_maps(argv[1], &(window.window));
	if (!syntaxe_error(&window.window) || !is_valid_map(window.window.maps))
		return (ft_printf("error"));
	if (!check_collectible((t_point){1, 1}, &(window.window)))
		return (ft_printf("error ac"));
	window.window.mlx = mlx_init();
	if (window.window.mlx == NULL)
	{
		cleanup(&window);
		printf("Erreur d'initialisation de la MiniLibX\n");
		return (1);
	}
	window.window.width = window.window.col_size * 32;
	window.window.height = window.window.row_size * 32;
	window.window.win = mlx_new_window(window.window.mlx, window.window.width,
			window.window.height, "So Long");
	if (window.window.win == NULL)
	{
		printf("Erreur de création de la fenêtre\n");
		cleanup(&window);
		return (1);
	}
	init_ghost(&window);
	load_images(&window);
	draw_map(&window);
	mlx_loop_hook(window.window.mlx, update_game, &window);
	mlx_loop(window.window.mlx);
	cleanup(&window);
	return (0);
}

/*

 -------------------------------------
|                  .                  |
| /!\ Attention free la list maps /!\ |
|                  .                  |
 -------------------------------------

*/