/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 00:13:47 by aderison          #+#    #+#             */
/*   Updated: 2024/08/07 20:56:07 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_collision(t_game *game, int keycode)
{
	int	left;
	int	right;
	int	top;
	int	bottom;

	left = (int)(round(game->pacman.x + 2)) / 32;
	right = (int)(round(game->pacman.x + 32 - 2)) / 32;
	top = (int)(round(game->pacman.y + 2)) / 32;
	bottom = (int)(round(game->pacman.y + 32 - 2)) / 32;
	if (is_wall(right + 1, top, game) && is_wall(left - 1, bottom, game)
		&& keycode == KEY_RIGHT)
		return (0);
	if (is_wall(right - 1, top, game) && keycode == KEY_LEFT)
		return (0);
	if (is_wall(right, bottom + 1, game) && keycode == KEY_DOWN)
		return (0);
	if (is_wall(right, bottom - 1, game) && keycode == KEY_UP)
		return (0);
	return (1);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_LEFT && is_collision(game, keycode))
	{
		game->pacman.dx = -3.0;
		game->pacman.dy = 0.0;
	}
	else if (keycode == KEY_RIGHT && is_collision(game, keycode))
	{
		game->pacman.dx = 3.0;
		game->pacman.dy = 0.0;
	}
	else if (keycode == KEY_DOWN && is_collision(game, keycode))
	{
		game->pacman.dx = 0.0;
		game->pacman.dy = 3.0;
	}
	else if (keycode == KEY_UP && is_collision(game, keycode))
	{
		game->pacman.dx = 0.0;
		game->pacman.dy = -3.0;
	}
	else if (keycode == KEY_ESC)
		exit(0);
	return (0);
}

void	move_ghost(t_game *game)
{
	t_astar	tastar;
	t_node	*result;
	float	target_y;
	float	dx;
	float	dy;
	float	length;
	t_node	*next_node;

	initialize_astar(&tastar, &(game->window), (t_point){game->ghost.x / 32,
		game->ghost.y / 32}, (t_point){(int)game->pacman.x / 32,
		(int)game->pacman.y / 32});
	fill_grid(&tastar, &(game->window));
	set_start_node(&tastar);
	result = astar(&tastar);
	if (result)
	{
		// Trouver le prochain nœud à partir du résultat (qui est l'arrivée)
		next_node = result;
		while (next_node->parent && next_node->parent->parent)
			next_node = next_node->parent;
		// Calculer la direction vers le prochain nœud du chemin
		float target_x = next_node->pos.x * 32; // Centre de la cellule
		target_y = next_node->pos.y * 32;
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
	else
	{
		ft_printf("No path found\n");
		game->ghost.dx = 0;
		game->ghost.dy = 0;
	}
	free_grid(&tastar);
}
#include <stdio.h>

int	game_loop(t_game *game)
{
	float	new_x;
	float	new_y;

	new_x = game->pacman.x + game->pacman.dx;
	new_y = game->pacman.y + game->pacman.dy;
	printf("Pacman position: x=%f, y=%f, dx=%f, dy=%f\n", game->pacman.x,
		game->pacman.y, game->pacman.dx, game->pacman.dy);
	move_wall((t_point){new_x, new_y}, game);
	mlx_clear_window(game->window.mlx, game->window.win);
	load_map(game);
	move_ghost(game);
	mlx_put_image_to_window(game->window.mlx, game->window.win,
		game->images.player, game->pacman.x, game->pacman.y);
	game->ghost.x += game->ghost.dx;
	game->ghost.y += game->ghost.dy;
	mlx_put_image_to_window(game->window.mlx, game->window.win,
		game->images.ghost, game->ghost.x, game->ghost.y);
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
	game->ghost.x = 27 * 32;
	game->ghost.y = 17 * 32;
	game->ghost.dx = 0;
	game->ghost.dy = 0;
	game->ghost.speed = 3.0f;
	load_images(game);
	draw_map(game);
	mlx_hook(game->window.win, 2, 1L << 0, (int (*)(int, void *))key_press,
		game);
	mlx_loop_hook(game->window.mlx, game_loop, game);
	mlx_loop(game->window.mlx);
}
