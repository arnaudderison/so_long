/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:09:58 by aderison          #+#    #+#             */
/*   Updated: 2024/08/16 03:32:44 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	end_game(t_game *game, char *msg)
{
	mlx_clear_window(game->window.mlx, game->window.win);
	mlx_string_put(game->window.mlx, game->window.win, game->window.width / 2
		- 50, game->window.height / 2, 0xFFFFFF, msg);
	game->gameOver = 1;
}
