/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 21:24:24 by aderison          #+#    #+#             */
/*   Updated: 2024/08/03 17:22:25 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPS_H
# define MAPS_H

# include "so_long.h"

typedef struct s_window
{
	char			**maps;
	int				row_size;
	int				col_size;
}					t_window;

typedef struct s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct s_node
{
	t_point			pos;
	int				f;
	int				g;
	int				h;
	struct s_node	*parent;
}					t_node;

typedef struct s_astar
{
	t_node			**grid;
	t_point			start;
	t_point			end;
	int				width;
	int				height;
}					t_astar;

int					syntaxe_error(t_window *win);
int					is_valid_map(char **map);
// int					is_valid(int row, int col, t_window *win);
// int					is_unblocked(t_window *win, int row, int col);
// int					is_destination(t_point src, t_point dest);
// int					calculate_hvalue(t_point src, t_point dest);
// int					check_src_dest(t_point src, t_point dest,
// t_window *win);
int					is_valid(t_astar *astar, int x, int y);
t_node				*create_node(int x, int y);
t_node				*astar(t_astar *astar);
int					heuristic(t_point a, t_point b);
void				free_grid(t_astar *astar);

#endif
