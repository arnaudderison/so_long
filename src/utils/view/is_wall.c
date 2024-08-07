/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_wall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:30:58 by aderison          #+#    #+#             */
/*   Updated: 2024/08/07 17:27:27 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_wall(int x, int y, t_game *game)
{
	return (game->window.maps[y][x] == '1');
}

void	move_wall(t_point dest, t_game *game)
{
	int	left;
	int	right;
	int	top;
	int	bottom;

	left = (int)(dest.x + 2) / 32;
	right = (int)(dest.x + 32 - 2) / 32;
	top = (int)(dest.y + 2) / 32;
	bottom = (int)(dest.y + 32 - 2) / 32;
	if (game->pacman.dx > 0)
	{
		if (!is_wall(right, top, game) && !is_wall(right, bottom, game))
			game->pacman.x = dest.x;
	}
	else if (game->pacman.dx < 0)
		if (!is_wall(left, top, game) && !is_wall(left, bottom, game))
			game->pacman.x = dest.x;
	if (game->pacman.dy > 0)
	{
		if (!is_wall(left, bottom, game) && !is_wall(right, bottom, game))
			game->pacman.y = dest.y;
	}
	else if (game->pacman.dy < 0)
		if (!is_wall(left, top, game) && !is_wall(right, top, game))
			game->pacman.y = dest.y;
}
