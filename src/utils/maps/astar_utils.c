/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astar_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 03:44:28 by aderison          #+#    #+#             */
/*   Updated: 2024/09/22 02:23:44 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

	if (!astar)
		return ;
	i = 0;
	while (i < astar->height && astar->grid[i])
	{
		ft_free(1, &astar->grid[i]);
		i++;
	}
	free(astar->grid);
	astar->grid = NULL;
}

int	heuristic(t_point a, t_point b)
{
	return (abs(a.x - b.x) + abs(a.y - b.y));
}

int	is_valid(t_astar *astar, int x, int y)
{
	// ft_printf("test %d\n", astar->grid[y][x].g);
	return (x >= 0 && x < astar->width && y >= 0 && y < astar->height
		&& astar->grid[y][x].g != -1);
}
