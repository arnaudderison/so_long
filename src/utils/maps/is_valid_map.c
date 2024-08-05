/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:01:20 by aderison          #+#    #+#             */
/*   Updated: 2024/08/05 04:21:51 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_collectible(t_point start, t_window *win)
{
	int		i;
	int		j;
	t_astar	tastar;
	t_node	*result;

	i = -1;
	while (++i < win->row_size)
	{
		j = -1;
		while (++j < win->col_size)
		{
			if (win->maps[i][j] == 'C')
			{
				initialize_astar(&tastar, win, start, (t_point){j, i});
				fill_grid(&tastar, win);
				set_start_node(&tastar);
				result = astar(&tastar);
				free_grid(&tastar);
				if (!result)
				{
					ft_printf("ERROR : %d %d\n", j, i);
					return (0);
				}
			}
		}
	}
	return (1);
}

static int	is_wall(char *line)
{
	int	len;

	len = ft_strlen(line);
	while (--len > 0)
		if (line[len - (ft_strchr(line, '\n') != NULL)] != '1')
			return (false);
	return (true);
}

static void	nb_items(char *line, int *items)
{
	int	i;

	i = -1;
	while (++i < ft_strlen(line))
	{
		if (line[i] == 'C')
			items[0] += 1;
		if (line[i] == 'P')
			items[1] += 1;
		if (line[i] == 'E')
			items[2] += 1;
	}
}

int	is_valid_map(char **map)
{
	int	items[3];
	int	i;

	if (!map || !*map)
		return (false);
	items[0] = 0;
	items[1] = 0;
	items[2] = 0;
	i = 0;
	if (!is_wall(map[i]))
		return (0);
	while (map[i])
	{
		if (map[i][0] != '1' || map[i][ft_strlen(map[i]) - 2] != '1')
			return (0);
		nb_items(map[i], items);
		if (!map[i + 1])
			if (!is_wall(map[i]))
				return (0);
		i++;
	}
	return (items[0] > 0 && items[1] == 1 && items[2] == 1);
}
