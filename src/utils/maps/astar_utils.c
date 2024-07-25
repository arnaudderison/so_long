/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astar_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 03:44:28 by aderison          #+#    #+#             */
/*   Updated: 2024/07/25 04:19:20 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	isValid(int row, int col, t_window *win)
{
	return (row >= 0) && (row < win->row_size) && (col >= 0)
		&& (col < win->col_size);
}

int	isUnBlocked(t_window *win, int row, int col)
{
	int		y;
	int		x;
	t_list	*line;

	y = -1;
	x = -1;
	line = win->maps;
	while (++y < row)
		line = line->next;
	if (((char *)line->content)[col] != '1')
		return (1);
	return (0);
}

int	isDestination(t_point src, t_point dest)
{
	return (src.y == dest.y && src.x == dest.x);
}

int	calculateHValue(t_point src, t_point dest)
{
	return (abs(src.y - dest.y) + abs(src.x - dest.x));
}
