/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 05:35:43 by aderison          #+#    #+#             */
/*   Updated: 2024/07/25 05:47:04 by aderison         ###   ########.fr       */
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
