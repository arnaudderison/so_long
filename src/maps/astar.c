/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 05:35:43 by aderison          #+#    #+#             */
/*   Updated: 2024/08/03 17:19:43 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static t_node	*get_lowest_f(t_node **open_set, int size)
{
	int		i;
	t_node	*lowest;
	int		lowest_index;

	i = 0;
	lowest = NULL;
	lowest_index = -1;
	while (i < size)
	{
		if (open_set[i] && (!lowest || open_set[i]->f < lowest->f))
		{
			lowest = open_set[i];
			lowest_index = i;
		}
		i++;
	}
	if (lowest_index != -1)
		open_set[lowest_index] = NULL;
	return (lowest);
}

static void	update_neighbor(t_astar *astar, t_node *current, t_node *neighbor,
		t_node **open_set)
{
	int	tentative_g;

	tentative_g = current->g + 1;
	if (tentative_g < neighbor->g)
	{
		neighbor->parent = current;
		neighbor->g = tentative_g;
		neighbor->f = neighbor->g + neighbor->h;
		if (!open_set[neighbor->pos.y * astar->width + neighbor->pos.x])
			open_set[neighbor->pos.y * astar->width
				+ neighbor->pos.x] = neighbor;
	}
}

static void	process_neighbors(t_astar *astar, t_node *current,
		t_node **open_set, t_node **closed_set)
{
	int		dx[4] = {0, 0, -1, 1};
	int		dy[4] = {-1, 1, 0, 0};
	int		i;
	int		new_x;
	int		new_y;
	t_node	*neighbor;

	i = 0;
	while (i < 4)
	{
		new_x = current->pos.x + dx[i];
		new_y = current->pos.y + dy[i];
		if (is_valid(astar, new_x, new_y))
		{
			neighbor = &astar->grid[new_y][new_x];
			if (!closed_set[new_y * astar->width + new_x])
				update_neighbor(astar, current, neighbor, open_set);
		}
		i++;
	}
}

t_node	*astar(t_astar *astar)
{
	t_node	**open_set;
	t_node	**closed_set;
	t_node	*current;
	int		size;

	size = astar->width * astar->height;
	open_set = calloc(size, sizeof(t_node *));
	closed_set = calloc(size, sizeof(t_node *));
	open_set[astar->start.y * astar->width
		+ astar->start.x] = &astar->grid[astar->start.y][astar->start.x];
	while ((current = get_lowest_f(open_set, size)))
	{
		if (current->pos.x == astar->end.x && current->pos.y == astar->end.y)
		{
			free(open_set);
			free(closed_set);
			return (current);
		}
		closed_set[current->pos.y * astar->width + current->pos.x] = current;
		process_neighbors(astar, current, open_set, closed_set);
	}
	free(open_set);
	free(closed_set);
	return (NULL);
}
