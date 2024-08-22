/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction_pac.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 23:14:45 by aderison          #+#    #+#             */
/*   Updated: 2024/08/22 00:49:19 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	direction_pac(t_game *game)
{
	if (game->pacman.dx > 0)
		mlx_put_image_to_window(game->window.mlx, game->window.win,
			game->images.player_right, game->pacman.x, game->pacman.y);
	if (game->pacman.dx < 0)
		mlx_put_image_to_window(game->window.mlx, game->window.win,
			game->images.player_left, game->pacman.x, game->pacman.y);
	if (game->pacman.dy > 0)
		mlx_put_image_to_window(game->window.mlx, game->window.win,
			game->images.player_down, game->pacman.x, game->pacman.y);
	if (game->pacman.dy < 0)
		mlx_put_image_to_window(game->window.mlx, game->window.win,
			game->images.player_up, game->pacman.x, game->pacman.y);
}

void	pacpac(t_game *game)
{
	if (game->ghost.frame_counter % 5 < 2)
		direction_pac(game);
	else
	{
		mlx_put_image_to_window(game->window.mlx, game->window.win,
			game->images.player, game->pacman.x, game->pacman.y);
	}
}
