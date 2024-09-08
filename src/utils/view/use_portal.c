/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_portal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 15:18:14 by aderison          #+#    #+#             */
/*   Updated: 2024/09/08 15:18:31 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	use_portal(int x, int y, t_game *game)
{
	if (game->window.maps[y][x] == 'E')
	{
		game->portal.x = x * 32;
		game->portal.y = y * 32;
	}
}
