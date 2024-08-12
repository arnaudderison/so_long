/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 00:13:47 by aderison          #+#    #+#             */
/*   Updated: 2024/08/12 05:35:52 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_pacman_ghost_collision(t_game *game)
{
	float	dx;
	float	dy;
	float	distance;

	dx = game->pacman.x - game->ghost.x + 16;
	dy = game->pacman.y - game->ghost.y + 16;
	distance = sqrt(dx * dx + dy * dy);
	return (distance < 18);
}

// Ajoutez cette fonction pour gérer la fin du jeu
static void	end_game(t_game *game)
{
	mlx_clear_window(game->window.mlx, game->window.win);
	mlx_string_put(game->window.mlx, game->window.win, game->window.width / 2
		- 50, game->window.height / 2, 0xFFFFFF, "Game Over!");
}

int	is_collision(t_game *game, int keycode)
{
	int	cell_x;
	int	cell_y;

	cell_x = (game->pacman.x + 16) / 32;
	cell_y = (game->pacman.y + 16) / 32;
	if (keycode == KEY_RIGHT)
		return (!is_wall(cell_x + 1, cell_y, game));
	else if (keycode == KEY_LEFT)
		return (!is_wall(cell_x - 1, cell_y, game));
	else if (keycode == KEY_DOWN)
		return (!is_wall(cell_x, cell_y + 1, game));
	else if (keycode == KEY_UP)
		return (!is_wall(cell_x, cell_y - 1, game));
	return (1);
}
#include <stdio.h>

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_LEFT && is_collision(game, keycode))
	{
		game->pacman.dx = -4.0;
		game->pacman.dy = 0.0;
		game->pacman.y = roundf(game->pacman.y / 32) * 32;
		// Alignement vertical
	}
	else if (keycode == KEY_RIGHT && is_collision(game, keycode))
	{
		game->pacman.dx = 4.0;
		game->pacman.dy = 0.0;
		game->pacman.y = roundf(game->pacman.y / 32) * 32;
		// Alignement vertical
	}
	else if (keycode == KEY_DOWN && is_collision(game, keycode))
	{
		game->pacman.dx = 0.0;
		game->pacman.dy = 4.0;
		game->pacman.x = roundf(game->pacman.x / 32) * 32;
		// Alignement horizontal
	}
	else if (keycode == KEY_UP && is_collision(game, keycode))
	{
		game->pacman.dx = 0.0;
		game->pacman.dy = -4.0;
		game->pacman.x = roundf(game->pacman.x / 32) * 32;
		// Alignement horizontal
	}
	else if (keycode == KEY_ESC)
		exit(0);
	return (0);
}

static void	calculate_ghost_direction(t_game *game, t_node *next_node)
{
	float	target_x;
	float	target_y;
	float	dx;
	float	dy;
	float	length;

	target_x = next_node->pos.x * 32 + 16;
	target_y = next_node->pos.y * 32 + 16;
	dx = target_x - game->ghost.x;
	dy = target_y - game->ghost.y;
	length = sqrt(dx * dx + dy * dy);
	if (length > 0)
	{
		game->ghost.dx = (dx / length) * game->ghost.speed;
		game->ghost.dy = (dy / length) * game->ghost.speed;
	}
	else
	{
		game->ghost.dx = 0;
		game->ghost.dy = 0;
	}
}

static t_node	*find_next_node(t_node *result)
{
	t_node	*next_node;

	next_node = result;
	while (next_node->parent && next_node->parent->parent)
		next_node = next_node->parent;
	return (next_node);
}

void	move_ghost(t_game *game)
{
	t_astar	tastar;
	t_node	*result;
	t_node	*next_node;
	t_point	ghost_pos;
	t_point	pacman_pos;

	ghost_pos = (t_point){(int)game->ghost.x / 32, (int)game->ghost.y / 32};
	pacman_pos = (t_point){(int)game->pacman.x / 32, (int)game->pacman.y / 32};
	initialize_astar(&tastar, &(game->window), ghost_pos, pacman_pos);
	fill_grid(&tastar, &(game->window));
	set_start_node(&tastar);
	result = astar(&tastar);
	if (result)
	{
		next_node = find_next_node(result);
		calculate_ghost_direction(game, next_node);
	}
	else
	{
		game->ghost.dx = 0;
		game->ghost.dy = 0;
	}
	free_grid(&tastar);
}

int	game_loop(t_game *game)
{
	float	new_x;
	float	new_y;
	int		cell_x;
	int		cell_y;

	if (game->gameOver)
		return (0);
	new_x = game->pacman.x + game->pacman.dx;
	new_y = game->pacman.y + game->pacman.dy;
	if (game->pacman.dx != 0)
	{
		cell_y = roundf(new_y / 32) * 32;
		if (fabsf(new_y - cell_y) < 4)
			new_y = cell_y;
	}
	if (game->pacman.dy != 0)
	{
		cell_x = roundf(new_x / 32) * 32;
		if (fabsf(new_x - cell_x) < 4)
			new_x = cell_x;
	}
	move_wall((t_point){new_x, new_y}, game);
	mlx_clear_window(game->window.mlx, game->window.win);
	load_map(game);
	if (game->ghost.frame_counter % 5 == 0)
		move_ghost(game);
	if (check_pacman_ghost_collision(game))
	{
		end_game(game);
		game->gameOver = 1;
		return (0);
	}
	mlx_put_image_to_window(game->window.mlx, game->window.win,
		game->images.player, game->pacman.x, game->pacman.y);
	game->ghost.x += game->ghost.dx;
	game->ghost.y += game->ghost.dy;
	mlx_put_image_to_window(game->window.mlx, game->window.win,
		game->images.ghost, game->ghost.x - 16, game->ghost.y - 16);
	game->ghost.frame_counter++;
	return (0);
}

void	window(t_game *game)
{
	game->window.mlx = mlx_init();
	if (game->window.mlx == NULL)
	{
		cleanup(game);
		return ;
	}
	game->window.width = (game->window.col_size - 1) * 32;
	game->window.height = game->window.row_size * 32;
	game->window.win = mlx_new_window(game->window.mlx, game->window.width,
			game->window.height, "So Long");
	if (game->window.win == NULL)
	{
		cleanup(game);
		return ;
	}
	game->pacman.dx = 2.0;
	game->pacman.dy = 0.0;
	game->ghost.x = 27 * 32 + 16;
	game->ghost.y = 17 * 32 + 16;
	game->ghost.dx = 0;
	game->ghost.dy = 0;
	game->ghost.speed = 3.5f;
	game->ghost.frame_counter = 0;
	game->gameOver = 0;
	load_images(game);
	draw_map(game);
	mlx_hook(game->window.win, 2, 0, (int (*)(int, void *))key_press, game);
	mlx_loop_hook(game->window.mlx, game_loop, game);
	mlx_loop(game->window.mlx);
}
