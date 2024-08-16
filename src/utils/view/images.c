/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 23:58:16 by aderison          #+#    #+#             */
/*   Updated: 2024/08/16 04:27:39 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	game->images.player = mlx_xpm_file_to_image(game->window.mlx,
			"./assets/xpm/pac.xpm", &img_width, &img_height);
}

void	cleanup(t_game *game)
{
	if (!game)
		return ;
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
	ft_free_matrice(1, &(game->window.maps));
}

int	close_window(t_game *game)
{
	cleanup(game);
	exit(0);
}
