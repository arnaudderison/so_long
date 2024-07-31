/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astar_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 03:44:28 by aderison          #+#    #+#             */
/*   Updated: 2024/07/30 22:43:00 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_valid(int row, int col, t_window *win)
{
	return (row >= 0) && (row < win->row_size) && (col >= 0)
		&& (col < win->col_size);
}

int	is_unblocked(t_window *win, int row, int col)
{
	int		y;
	int		x;
	char	*line;

	y = -1;
	x = -1;
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

int	calculate_hvalue(t_point src, t_point dest)
{
	return (abs(src.y - dest.y) + abs(src.x - dest.x));
}

void	init_node_details(t_astar *astar, t_window *win)
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
			astar->node_details[i][j].parent.y = -1;
			astar->node_details[i][j].parent.x = -1;
		}
	}
}
