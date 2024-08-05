/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 00:13:47 by aderison          #+#    #+#             */
/*   Updated: 2024/08/06 00:23:42 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	window(t_game *game)
{
	game->window.mlx = mlx_init();
	if (game->window.mlx == NULL)
	{
		cleanup(game);
		return ;
	}
	game->window.width = game->window.col_size * 32;
	game->window.height = game->window.row_size * 32;
	game->window.win = mlx_new_window(game->window.mlx, game->window.width,
			game->window.height, "So Long");
	if (game->window.win == NULL)
	{
		cleanup(game);
		return ;
	}
	load_images(game);
	draw_map(game);
	mlx_loop(game->window.mlx);
}
