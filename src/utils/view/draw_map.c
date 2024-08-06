/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 00:01:01 by aderison          #+#    #+#             */
/*   Updated: 2024/08/06 06:17:07 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*player_set(t_game *game, int x, int y)
{
	game->pacman.x = x * 32;
	game->pacman.y = y * 32;
	game->pacman.dx = game->pacman.dx;
	game->pacman.dy = game->pacman.dy;
	return (game->images.player);
}

void	draw_map(t_game *game)
{
	int		y;
	int		x;
	void	*img_to_use;

	y = -1;
	while (++y < game->window.row_size)
	{
		x = -1;
		while (++x < game->window.col_size)
		{
			img_to_use = NULL;
			if (game->window.maps[y][x] == '1')
				img_to_use = game->images.wall;
			else if (game->window.maps[y][x] == 'C')
				img_to_use = game->images.collectible;
			else if (game->window.maps[y][x] == 'P')
				img_to_use = player_set(game, x, y);
			else if (game->window.maps[y][x] == 'G')
				img_to_use = game->images.ghost;
			else
				img_to_use = game->images.background;
			mlx_put_image_to_window(game->window.mlx, game->window.win,
				img_to_use, x * 32, y * 32);
		}
	}
}

void	load_map(t_game *game)
{
	int		y;
	int		x;
	void	*img_to_use;

	y = -1;
	while (++y < game->window.row_size)
	{
		x = -1;
		while (++x < game->window.col_size - 1)
		{
			img_to_use = NULL;
			if (game->window.maps[y][x] == '1')
				img_to_use = game->images.wall;
			else if (game->window.maps[y][x] == 'C')
				img_to_use = game->images.collectible;
			else if (game->window.maps[y][x] == 'G')
				img_to_use = game->images.ghost;
			else
				img_to_use = game->images.background;
			mlx_put_image_to_window(game->window.mlx, game->window.win,
				img_to_use, x * 32, y * 32);
		}
	}
}
