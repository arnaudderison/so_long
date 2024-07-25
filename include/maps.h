/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 21:24:24 by aderison          #+#    #+#             */
/*   Updated: 2024/07/25 20:57:57 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPS_H
# define MAPS_H

# include "so_long.h"

typedef struct s_window
{
	char	**maps;
	int		row_size;
	int		col_size;
}			t_window;

typedef struct s_point
{
	int		x;
	int		y;
}			t_point;

typedef struct s_node
{
	int		f;
	int		g;
	int		h;
	t_point	parent;
}			t_node;

typedef struct s_cell
{
	t_point	point;
	t_node	node;
}			t_cell;

typedef struct s_astar
{
	t_list	*closed_list;
	t_node	**node_details;
	t_point	src;
	t_point	dest;
	t_point	*open_list;
	int		open_size;
}			t_astar;

int			syntaxe_error(t_window *win);
int			is_valid_map(char **map);
int			isValid(int row, int col, t_window *win);
int			isUnBlocked(t_window *win, int row, int col);
int			isDestination(t_point src, t_point dest);
int			calculateHValue(t_point src, t_point dest);

#endif
