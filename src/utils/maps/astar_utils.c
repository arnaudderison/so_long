/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astar_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 03:44:28 by aderison          #+#    #+#             */
/*   Updated: 2024/08/03 17:36:36 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_unblocked(t_window *win, int row, int col)
{
	int		y;
	char	*line;

	y = -1;
	while (++y < row)
		line = (win->maps)[y];
	if (line[col] == '1')
		return (0);
	return (1);
}

int	is_destination(t_point src, t_point dest)
{
	return (src.y == dest.y && src.x == dest.x);
}

t_node	*create_node(int x, int y)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->pos.x = x;
	node->pos.y = y;
	node->f = 0;
	node->g = 0;
	node->h = 0;
	node->parent = NULL;
	return (node);
}

void	free_grid(t_astar *astar)
{
	int	i;

	i = 0;
	while (i < astar->height)
	{
		free(astar->grid[i]);
		i++;
	}
	free(astar->grid);
}

int	heuristic(t_point a, t_point b)
{
	return (abs(a.x - b.x) + abs(a.y - b.y));
}

int	is_valid(t_astar *astar, int x, int y)
{
	return (x >= 0 && x < astar->width && y >= 0 && y < astar->height
		&& astar->grid[y][x].g != -1);
}
