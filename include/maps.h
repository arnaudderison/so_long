/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 21:24:24 by aderison          #+#    #+#             */
/*   Updated: 2024/09/22 02:21:46 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPS_H
# define MAPS_H

# include "so_long.h"

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

typedef struct s_images
{
	void			*wall;
	void			*ghost;
	void			*collectible;
	void			*background;
	void			*player;
	void			*player_right;
	void			*player_left;
	void			*player_up;
	void			*player_down;
	void			*exit;
	void			*portal;
}					t_images;

typedef struct s_window
{
	char			**maps;
	int				row_size;
	int				col_size;
	void			*mlx;
	void			*win;
	void			*img;
	int				width;
	int				height;
	int				col_count;
}					t_window;

typedef struct s_ghost
{
	int				x;
	int				y;
	int				dx;
	int				dy;
	float			speed;
	void			*img;
	t_node			*path;
	int				frame_counter;
	int				available;
}					t_ghost;

typedef struct
{
	float			x;
	float			y;
	float			dx;
	float			dy;
	void			*img;
}					t_pacman;

typedef struct s_portal
{
	unsigned int	x;
	unsigned int	y;
}					t_portal;

typedef struct s_game
{
	t_window		window;
	t_images		images;
	t_ghost			ghost;
	t_pacman		pacman;
	t_portal		portal;
	int				gameOver;
	unsigned int	point;
	int				move;
}					t_game;

int					syntaxe_error(t_window *win);
int					is_valid_map(t_window *win);
int					is_valid(t_astar *astar, int x, int y);
t_node				*create_node(int x, int y);
t_node				*astar(t_astar *astar);
int					heuristic(t_point a, t_point b);
void				free_grid(t_astar *astar);
void				initialize_astar(t_astar *tastar, t_window *window,
						t_point src, t_point dest);
void				fill_grid(t_astar *tastar, t_window *window);
void				set_start_node(t_astar *tastar);
int					process_result(t_node *result);
int					check_collectible(t_point start, t_window *win);
int					is_wall(int x, int y, t_game *game);
int					count_c(t_window *win);

#endif
