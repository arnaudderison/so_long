/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 00:13:47 by aderison          #+#    #+#             */
/*   Updated: 2024/08/06 06:47:04 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>

#define KEY_A 0
#define KEY_S 1
#define KEY_D 2
#define KEY_W 13
#define KEY_LEFT 123
#define KEY_RIGHT 124
#define KEY_DOWN 125
#define KEY_UP 126
#define KEY_ESC 53

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_LEFT)
	{
		game->pacman.dx = -3.0;
		game->pacman.dy = 0.0;
	}
	else if (keycode == KEY_RIGHT)
	{
		game->pacman.dx = 3.0;
		game->pacman.dy = 0.0;
	}
	else if (keycode == KEY_DOWN)
	{
		game->pacman.dx = 0.0;
		game->pacman.dy = 3.0;
	}
	else if (keycode == KEY_UP)
	{
		game->pacman.dx = 0.0;
		game->pacman.dy = -3.0;
	}
	else if (keycode == KEY_ESC)
		exit(0);
	return (0);
}

int	game_loop(t_game *game)
{
	float	new_x;
	float	new_y;
	int		left;
	int		right;
	int		top;
	int		bottom;

	new_x = game->pacman.x + game->pacman.dx;
	new_y = game->pacman.y + game->pacman.dy;
	// Vérifier la collision avec les murs
	left = (int)new_x / 32;
	right = (int)(new_x + 32 - 1) / 32;
	top = (int)new_y / 32;
	bottom = (int)(new_y + 32 - 1) / 32;
	// Vérification horizontale
	if (game->pacman.dx > 0) // Se déplace vers la droite
	{
		if (game->window.maps[top][right] != '1'
			&& game->window.maps[bottom][right] != '1')
			game->pacman.x = new_x;
	}
	else if (game->pacman.dx < 0) // Se déplace vers la gauche
	{
		if (game->window.maps[top][left] != '1'
			&& game->window.maps[bottom][left] != '1')
			game->pacman.x = new_x;
	}
	// Vérification verticale
	if (game->pacman.dy > 0) // Se déplace vers le bas
	{
		if (game->window.maps[bottom][left] != '1'
			&& game->window.maps[bottom][right] != '1')
			game->pacman.y = new_y;
	}
	else if (game->pacman.dy < 0) // Se déplace vers le haut
	{
		if (game->window.maps[top][left] != '1'
			&& game->window.maps[top][right] != '1')
			game->pacman.y = new_y;
	}
	if (game->pacman.x < 32)
		game->pacman.x = 32;
	if (game->pacman.x > ((game->window.col_size) - 3) * 32 - 1)
		game->pacman.x = (((game->window.col_size) - 3) * 32 - 1);
	if (game->pacman.y < 32)
		game->pacman.y = 32;
	if (game->pacman.y > ((game->window.row_size) - 2) * 32)
		game->pacman.y = ((game->window.row_size) - 2) * 32;
	mlx_clear_window(game->window.mlx, game->window.win);
	load_map(game);
	mlx_put_image_to_window(game->window.mlx, game->window.win,
		game->images.player, game->pacman.x, game->pacman.y);
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
	game->pacman.dx = 0.0;
	game->pacman.dy = 0.0;
	load_images(game);
	draw_map(game);
	mlx_hook(game->window.win, 2, 1L << 0, (int (*)(int, void *))key_press,
		game);
	mlx_loop_hook(game->window.mlx, game_loop, game);
	mlx_loop(game->window.mlx);
}
