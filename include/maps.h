/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 21:24:24 by aderison          #+#    #+#             */
/*   Updated: 2024/08/06 00:18:31 by aderison         ###   ########.fr       */
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
	void			*exit;
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
}					t_window;

typedef struct s_ghost
{
	int				x;
	int				y;
	float			pixel_x;
	float			pixel_y;
	int				current_target;
	int				num_targets;
	float			speed;
	t_point			targets[100];
	int				frame_count;
	void			*img;
	t_node			*path;
	int				path_index;
}					t_ghost;

typedef struct s_game
{
	t_window		window;
	t_images		images;
	t_ghost			ghost;
}					t_game;

int					syntaxe_error(t_window *win);
int					is_valid_map(char **map);
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
void				print_path(t_node *end);
void				load_images(t_game *game);
void				cleanup(t_game *game);
int					close_window(t_game *game);
void				draw_map(t_game *game);
void				window(t_game *game);

#endif
