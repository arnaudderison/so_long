/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ghost.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 01:13:55 by aderison          #+#    #+#             */
/*   Updated: 2024/08/19 20:35:21 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	calculate_ghost_direction(t_game *game, t_node *next_node)
{
	float	target_x;
	float	target_y;
	float	dx;
	float	dy;
	float	length;

	target_x = next_node->pos.x * 32 + 16;
	target_y = next_node->pos.y * 32 + 16;
	dx = target_x - game->ghost.x;
	dy = target_y - game->ghost.y;
	length = sqrt(dx * dx + dy * dy);
	if (length > 0)
	{
		game->ghost.dx = (dx / length) * game->ghost.speed;
		game->ghost.dy = (dy / length) * game->ghost.speed;
	}
	else
	{
		game->ghost.dx = 0;
		game->ghost.dy = 0;
	}
}

static t_node	*find_next_node(t_node *result)
{
	t_node	*next_node;

	next_node = result;
	while (next_node->parent && next_node->parent->parent)
		next_node = next_node->parent;
	return (next_node);
}

void	move_ghost(t_game *game)
{
	t_astar	tastar;
	t_node	*result;
	t_node	*next_node;
	t_point	ghost_pos;
	t_point	pacman_pos;

	ghost_pos = (t_point){(int)game->ghost.x / 32, (int)game->ghost.y / 32};
	pacman_pos = (t_point){(int)game->pacman.x / 32, (int)game->pacman.y / 32};
	initialize_astar(&tastar, &(game->window), ghost_pos, pacman_pos);
	fill_grid(&tastar, &(game->window));
	set_start_node(&tastar);
	result = astar(&tastar);
	if (result)
	{
		next_node = find_next_node(result);
		calculate_ghost_direction(game, next_node);
	}
	else
	{
		game->ghost.dx = 0;
		game->ghost.dy = 0;
	}
	free_grid(&tastar);
}
