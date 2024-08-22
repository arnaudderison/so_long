/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 00:01:01 by aderison          #+#    #+#             */
/*   Updated: 2024/08/22 16:59:25 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	*player_set(t_game *game, int x, int y)
{
	game->pacman.x = x * 32;
	game->pacman.y = y * 32;
	game->pacman.dx = game->pacman.dx;
	game->pacman.dy = game->pacman.dy;
	return (game->images.player);
}

static void	*ghost_set(t_game *game, int x, int y)
{
	game->ghost.x = x * 32 + 16;
	game->ghost.y = y * 32 + 16;
	game->ghost.dx = game->ghost.dx;
	game->ghost.dy = game->ghost.dy;
	game->ghost.available = 1;
	return (game->images.ghost);
}

int	count_c(t_window *win)
{
	int	x;
	int	y;
	int	c_count;

	y = -1;
	c_count = 0;
	while (++y < win->row_size)
	{
		x = -1;
		while (++x < win->col_size - 1)
			if (win->maps[y][x] == 'C')
				c_count++;
	}
	return (c_count);
}

void	use_portal(int x, int y, t_game *game)
{
	if (game->window.maps[y][x] == 'E')
	{
		game->portal.x = x * 32;
		game->portal.y = y * 32;
	}
}

void	draw_map(t_game *game)
{
	int		y;
	int		x;
	void	*img_to_use;

	y = -1;
	while (++y < game->window.row_size - 1)
	{
		x = -1;
		while (++x < game->window.col_size)
		{
			if (game->window.maps[y][x] == '1')
				img_to_use = game->images.wall;
			else if (game->window.maps[y][x] == 'C')
				img_to_use = game->images.collectible;
			else if (game->window.maps[y][x] == 'P')
				img_to_use = player_set(game, x, y);
			else if (game->window.maps[y][x] == 'G')
				img_to_use = ghost_set(game, x, y);
			else
				img_to_use = game->images.background;
			mlx_put_image_to_window(game->window.mlx, game->window.win,
				img_to_use, x * 32, y * 32);
			use_portal(x, y, game);
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
			else
				img_to_use = game->images.background;
			mlx_put_image_to_window(game->window.mlx, game->window.win,
				img_to_use, x * 32, y * 32);
		}
	}
}
