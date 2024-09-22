/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 00:13:47 by aderison          #+#    #+#             */
/*   Updated: 2024/09/22 18:00:47 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	if (keycode == KEY_A && is_collision(game, keycode))
	{
		set_direction(&(game->pacman), -SPEED, 0.0, game);
		game->pacman.y = roundf(game->pacman.y / 32) * 32;
	}
	else if (keycode == KEY_D && is_collision(game, keycode))
	{
		set_direction(&(game->pacman), SPEED, 0.0, game);
		game->pacman.y = roundf(game->pacman.y / 32) * 32;
	}
	else if (keycode == KEY_S && is_collision(game, keycode))
	{
		set_direction(&(game->pacman), 0.0, SPEED, game);
		game->pacman.x = roundf(game->pacman.x / 32) * 32;
	}
	else if (keycode == KEY_W && is_collision(game, keycode))
	{
		set_direction(&(game->pacman), 0.0, -SPEED, game);
		game->pacman.x = roundf(game->pacman.x / 32) * 32;
	}
	else if (keycode == KEY_ESC)
		return (system("leaks so_long"), exit(0), 0);
	return (0);
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
	mlx_hook(game->window.win, 2, 0, key_press, game);
	mlx_loop_hook(game->window.mlx, game_loop, game);
	mlx_loop(game->window.mlx);
}
