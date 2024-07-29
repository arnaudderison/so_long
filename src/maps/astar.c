/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 05:35:43 by aderison          #+#    #+#             */
/*   Updated: 2024/07/26 03:32:16 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	init_node_details(t_astar *astar, t_window *win)
{
	int	i;
	int	j;

	i = -1;
	while (++i < win->row_size)
	{
		j = -1;
		while (++j < win->col_size)
		{
			astar->node_details[i][j].f = -1;
			astar->node_details[i][j].g = -1;
			astar->node_details[i][j].h = -1;
			astar->node_details[i][j].parent.row = -1;
			astar->node_details[i][j].parent.col = -1;
		}
	}
}

void	add_to_open_list(t_astar *astar, t_point point, t_node node)
{
	astar->open_list[astar->open_size] = point;
	astar->node_details[point.row][point.col] = node;
	astar->open_size++;
}

void	update_node(t_node *node, float f, float g, float h, t_point parent)
{
	node->f = f;
	node->g = g;
	node->h = h;
	node->parent = parent;
}
