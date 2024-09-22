/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:30:58 by aderison          #+#    #+#             */
/*   Updated: 2024/09/22 17:47:42 by aderison         ###   ########.fr       */
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

int	check_pacman_ghost_collision(t_game *game)
{
	float	dx;
	float	dy;
	float	distance;

	dx = game->pacman.x - game->ghost.x + 16;
	dy = game->pacman.y - game->ghost.y + 16;
	distance = sqrt(dx * dx + dy * dy);
	return (distance < 16);
}

int	check_pacman_portal_collision(t_game *game)
{
	int	dx;
	int	dy;
	int	distance;

	if (!game)
		return (0);
	dx = (int)game->pacman.x - game->portal.x;
	dy = (int)game->pacman.y - game->portal.y;
	distance = sqrt(dx * dx + dy * dy);
	return (distance < 16);
}

int	is_collision(t_game *game, int keycode)
{
	int	cell_x;
	int	cell_y;

	cell_x = (game->pacman.x + 16) / 32;
	cell_y = (game->pacman.y + 16) / 32;
	if (keycode == KEY_D)
		return (!is_wall(cell_x + 1, cell_y, game));
	else if (keycode == KEY_A)
		return (!is_wall(cell_x - 1, cell_y, game));
	else if (keycode == KEY_S)
		return (!is_wall(cell_x, cell_y + 1, game));
	else if (keycode == KEY_W)
		return (!is_wall(cell_x, cell_y - 1, game));
	return (1);
}
