/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 00:13:47 by aderison          #+#    #+#             */
/*   Updated: 2024/08/21 05:38:32 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>

void	display_score(t_game *game)
{
	char	score_str[20];
	char	point_str[20];
	int		score_x;
	int		score_y;

	ft_snprintf(score_str, sizeof(score_str), "Score: %d", game->point);
	ft_snprintf(point_str, sizeof(score_str), "Move: %d", game->move);
	score_x = game->window.width / 2 - (ft_strlen(score_str) * 5);
	score_y = 30;
	mlx_string_put(game->window.mlx, game->window.win, score_x, score_y,
		0xFFFFFF, score_str);
	mlx_string_put(game->window.mlx, game->window.win, score_x, score_y + 15,
		0xFFFFFF, point_str);
}

void	set_direction(t_pacman *pac, float dx, float dy, t_game *game)
{
	pac->dx = dx;
	pac->dy = dy;
	game->move++;
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_LEFT && is_collision(game, keycode))
	{
		set_direction(&(game->pacman), -4.0, 0.0, game);
		game->pacman.y = roundf(game->pacman.y / 32) * 32;
	}
	else if (keycode == KEY_RIGHT && is_collision(game, keycode))
	{
		set_direction(&(game->pacman), 4.0, 0.0, game);
		game->pacman.y = roundf(game->pacman.y / 32) * 32;
	}
	else if (keycode == KEY_DOWN && is_collision(game, keycode))
	{
		set_direction(&(game->pacman), 0.0, 4.0, game);
		game->pacman.x = roundf(game->pacman.x / 32) * 32;
	}
	else if (keycode == KEY_UP && is_collision(game, keycode))
	{
		set_direction(&(game->pacman), 0.0, -4.0, game);
		game->pacman.x = roundf(game->pacman.x / 32) * 32;
	}
	else if (keycode == KEY_ESC)
		exit(0);
	return (0);
}

void	portal(t_game *game)
{
	int		y;
	int		x;
	void	*img_to_use;

	mlx_clear_window(game->window.mlx, game->window.win);
	game->gameOver = -42;
	y = -1;
	while (++y < game->window.row_size)
	{
		x = -1;
		while (++x < game->window.col_size - 1)
		{
			img_to_use = NULL;
			if (game->window.maps[y][x] == '1')
				img_to_use = game->images.wall;
			else if (game->window.maps[y][x] == 'E')
				img_to_use = game->images.portal;
			else
				img_to_use = game->images.background;
			mlx_put_image_to_window(game->window.mlx, game->window.win,
				img_to_use, x * 32, y * 32);
		}
	}
}

int	is_win(t_game *game)
{
	if (game->window.maps[(int)(game->pacman.y) / 32][(int)(game->pacman.x)
		/ 32] == 'C')
	{
		game->window.maps[(int)game->pacman.y / 32][(int)game->pacman.x
			/ 32] = '0';
		game->window.col_count--;
		game->point++;
		if (game->window.col_count == 0)
			return (portal(game), 1);
	}
	return (0);
}

int	game_loop(t_game *game)
{
	float	new_x;
	float	new_y;

	if (game->gameOver == 1)
		return (0);
	new_x = game->pacman.x + game->pacman.dx;
	new_y = game->pacman.y + game->pacman.dy;
	move_wall((t_point){new_x, new_y}, game);
	mlx_clear_window(game->window.mlx, game->window.win);
	if (is_win(game) == 1)
		ft_printf("Points: %d\n", game->point);
	if (game->gameOver == -42)
	{
		ft_printf("x: %d y: %d \n", game->portal.x, game->portal.y);
		if (check_pacman_portal_collision(game))
			return (ft_printf("collision"), end_game(game, "WIN"), 0);
		portal(game);
	}
	else
		load_map(game);
	if (game->ghost.frame_counter % 5 == 0 && game->ghost.available)
		move_ghost(game);
	if (check_pacman_ghost_collision(game))
		return (end_game(game, "Game Over!"), 0);
	display_score(game);
	pacpac(game);
	game->ghost.x += game->ghost.dx;
	game->ghost.y += game->ghost.dy;
	mlx_put_image_to_window(game->window.mlx, game->window.win,
		game->images.ghost, game->ghost.x - 16, game->ghost.y - 16);
	return (game->ghost.frame_counter++, 0);
}

void	window(t_game *game)
{
	game->window.mlx = mlx_init();
	if (game->window.mlx == NULL)
	{
		cleanup(game);
		return ;
	}
	game->window.width = (game->window.col_size - 1) * 32;
	game->window.height = game->window.row_size * 32;
	game->window.win = mlx_new_window(game->window.mlx, game->window.width,
			game->window.height, "So Long");
	if (game->window.win == NULL)
	{
		cleanup(game);
		return ;
	}
	game->portal.x = 0;
	game->portal.y = 0;
	game->move = 0;
	load_images(game);
	init_game(game);
	game->window.col_count = count_c(&game->window);
	draw_map(game);
	mlx_hook(game->window.win, 2, 0, (int (*)(int, void *))key_press, game);
	mlx_loop_hook(game->window.mlx, game_loop, game);
	mlx_loop(game->window.mlx);
}
