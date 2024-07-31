/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 05:35:43 by aderison          #+#    #+#             */
/*   Updated: 2024/07/30 22:40:26 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// static void	add_to_open_list(t_astar *astar, t_point point, t_node node)
// {
// 	astar->open_list[astar->open_size] = point;
// 	astar->node_details[point.y][point.x] = node;
// 	astar->open_size++;
// }

// static void	remove_from_open_list(t_cell *open_list, int *open_list_size,
// 		int index)
// {
// 	open_list[index] = open_list[*open_list_size - 1];
// 	(*open_list_size)--;
// }

// static void	update_node(t_node *node, int f, int g, int h, t_point parent)
// {
// 	node->f = f;
// 	node->g = g;
// 	node->h = h;
// 	node->parent = parent;
// }

void	astar(char **grid, t_point src, t_point dest, t_window *win)
{
	// t_astar	astar;
	if (!grid || !*grid)
		return ;
	if (!check_src_dest(src, dest, win))
		return ;
}
