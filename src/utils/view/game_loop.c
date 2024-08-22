/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:23:26 by aderison          #+#    #+#             */
/*   Updated: 2024/08/22 16:12:18 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	portal(t_game *game)
{
	int		y;
	int		x;
	void	*img_to_use;

	mlx_clear_window(game->window.mlx, game->window.win);
	game->gameOver = -42;
	y = -1;
	while (++y < game->window.row_size)
	{
		x = -1;
		while (++x < game->window.col_size - 1)
		{
			img_to_use = NULL;
			if (game->window.maps[y][x] == '1')
				img_to_use = game->images.wall;
			else if (game->window.maps[y][x] == 'E')
				img_to_use = game->images.portal;
			else
				img_to_use = game->images.background;
			mlx_put_image_to_window(game->window.mlx, game->window.win,
				img_to_use, x * 32, y * 32);
		}
	}
}

int	is_win(t_game *game)
{
	if (game->window.maps[(int)(game->pacman.y + 16) / 32][(int)(game->pacman.x
			+ 16) / 32] == 'C')
	{
		game->window.maps[(int)(game->pacman.y + 16) / 32][(int)(game->pacman.x
				+ 16) / 32] = '0';
		game->window.col_count--;
		game->point++;
		if (game->window.col_count == 0)
			return (portal(game), 1);
	}
	return (0);
}

static int	maps_process(t_game *game)
{
	if (game->gameOver == -42)
	{
		if (check_pacman_portal_collision(game))
			return (end_game(game, "WIN"), 0);
		portal(game);
	}
	else
		load_map(game);
	return (1);
}

int	game_loop(t_game *game)
{
	float	new_x;
	float	new_y;

	if (game->gameOver == 1)
		return (0);
	new_x = game->pacman.x + game->pacman.dx;
	new_y = game->pacman.y + game->pacman.dy;
	move_wall((t_point){new_x, new_y}, game);
	mlx_clear_window(game->window.mlx, game->window.win);
	is_win(game);
	maps_process(game);
	if (game->ghost.frame_counter % 1 == 0 && game->ghost.available)
		move_ghost(game);
	if (check_pacman_ghost_collision(game))
		return (end_game(game, "Game Over!"), 0);
	display_score(game);
	pacpac(game);
	game->ghost.x += game->ghost.dx;
	game->ghost.y += game->ghost.dy;
	mlx_put_image_to_window(game->window.mlx, game->window.win,
		game->images.ghost, game->ghost.x - 16, game->ghost.y - 16);
	return (game->ghost.frame_counter++, 0);
}
