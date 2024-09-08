/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 07:06:30 by aderison          #+#    #+#             */
/*   Updated: 2024/09/08 15:18:51 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft.h"
# include "maps.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>

# define RED "\x1B[31m"
# define GREEN "\x1B[32m"
# define YELLOW "\x1B[33m"
# define BLUE "\x1B[34m"
# define MAG "\x1B[35m"
# define CYN "\x1B[36m"
# define RESET "\x1B[0m"

# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_W 13
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define KEY_UP 126
# define KEY_ESC 53

# define SPEED 4.0

# define ARG_ERR "Number(s) of arg(s) is invalid"
# define NULL_PTR "Pointer NULL"

typedef enum e_bool
{
	false,
	true
}		t_bool;

t_bool	file_exist(const char *path);
t_bool	file_extention(const char *path, const char *ext);
t_bool	line_checkchr(char *line);
t_bool	line_checknbr(char *line, int size);
void	init_maps(char *path, t_window *win);
void	load_images(t_game *game);
void	cleanup(t_game *game);
int		close_window(t_game *game);
void	draw_map(t_game *game);
void	window(t_game *game);
void	load_map(t_game *game);
void	move_wall(t_point dest, t_game *game);
int		is_collision(t_game *game, int keycode);
int		check_pacman_ghost_collision(t_game *game);
void	end_game(t_game *game, char *msg);
void	move_ghost(t_game *game);
void	init_game(t_game *game);
int		ft_snprintf(char *str, size_t size, const char *format, ...);
void	pacpac(t_game *game);
void	set_direction(t_pacman *pac, float dx, float dy, t_game *game);
int		check_pacman_portal_collision(t_game *game);
void	display_score(t_game *game);
int		game_loop(t_game *game);
void	use_portal(int x, int y, t_game *game);

#endif
