/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 00:13:47 by aderison          #+#    #+#             */
/*   Updated: 2024/08/16 04:44:05 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>

void	set_direction(t_pacman *pac, float dx, float dy)
{
	pac->dx = dx;
	pac->dy = dy;
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_LEFT && is_collision(game, keycode))
	{
		set_direction(&(game->pacman), -4.0, 0.0);
		game->pacman.y = roundf(game->pacman.y / 32) * 32;
	}
	else if (keycode == KEY_RIGHT && is_collision(game, keycode))
	{
		set_direction(&(game->pacman), 4.0, 0.0);
		game->pacman.y = roundf(game->pacman.y / 32) * 32;
	}
	else if (keycode == KEY_DOWN && is_collision(game, keycode))
	{
		set_direction(&(game->pacman), 0.0, 4.0);
		game->pacman.x = roundf(game->pacman.x / 32) * 32;
	}
	else if (keycode == KEY_UP && is_collision(game, keycode))
	{
		set_direction(&(game->pacman), 0.0, -4.0);
		game->pacman.x = roundf(game->pacman.x / 32) * 32;
	}
	else if (keycode == KEY_ESC)
		exit(0);
	return (0);
}

int	is_win(t_game *game)
{
	if (game->window.maps[(int)(game->pacman.y) / 32][(int)(game->pacman.x)
		/ 32] == 'C')
	{
		game->window.maps[(int)game->pacman.y / 32][(int)game->pacman.x
			/ 32] = '0';
		game->window.col_count--;
		if (game->window.col_count == 0)
			return (end_game(game, "WIn"), 1);
	}
	return (0);
}

int	game_loop(t_game *game)
{
	float	new_x;
	float	new_y;

	if (game->gameOver)
		return (0);
	new_x = game->pacman.x + game->pacman.dx;
	new_y = game->pacman.y + game->pacman.dy;
	move_wall((t_point){new_x, new_y}, game);
	mlx_clear_window(game->window.mlx, game->window.win);
	load_map(game);
	if (game->ghost.frame_counter % 5 == 0)
		move_ghost(game);
	if (check_pacman_ghost_collision(game))
		return (end_game(game, "Game Over!"), 0);
	if (is_win(game) == 1)
		return (0);
	mlx_put_image_to_window(game->window.mlx, game->window.win,
		game->images.player, game->pacman.x, game->pacman.y);
	game->ghost.x += game->ghost.dx;
	game->ghost.y += game->ghost.dy;
	mlx_put_image_to_window(game->window.mlx, game->window.win,
		game->images.ghost, game->ghost.x - 16, game->ghost.y - 16);
	return (game->ghost.frame_counter++, 0);
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
	game->pacman.dx = 0.0;
	game->pacman.dy = 0.0;
	game->ghost.dx = 0;
	game->ghost.dy = 0;
	game->ghost.speed = 3.5f;
	game->ghost.frame_counter = 0;
	game->gameOver = 0;
	game->window.col_count = 0;
	load_images(game);
	game->window.col_count = count_c(&game->window);
	draw_map(game);
	mlx_hook(game->window.win, 2, 0, (int (*)(int, void *))key_press, game);
	mlx_loop_hook(game->window.mlx, game_loop, game);
	mlx_loop(game->window.mlx);
}
