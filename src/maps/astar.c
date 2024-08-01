/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 05:35:43 by aderison          #+#    #+#             */
/*   Updated: 2024/08/01 21:06:47 by aderison         ###   ########.fr       */
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

void	init_astar(t_astar *astar, t_window *win, t_point src, t_point dest)
{
	int	i;

	if (!astar || !win)
		return ;
	i = -1;
	astar->closed_list = malloc(sizeof(int *) * (win->row_size + 1));
	while (++i < win->row_size)
		astar->closed_list[i] = ft_calloc(sizeof(int), (win->col_size + 1));
	i = -1;
	astar->node_details = malloc(sizeof(t_node *) * (win->row_size + 1));
	while (++i < win->row_size)
		astar->node_details[i] = malloc(sizeof(t_node) * (win->col_size + 1));
	i = -1;
	astar->open_list = malloc(sizeof(t_point) * (win->row_size * win->col_size
				+ 1));
	astar->src = src;
	astar->dest = dest;
}

void	astar(char **grid, t_point src, t_point dest, t_window *win)
{
	t_astar	astar;

	if (!grid || !*grid)
		return ;
	if (!check_src_dest(src, dest, win))
		return ;
	init_astar(&astar, win, t_point src, t_point dest);
}
