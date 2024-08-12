/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:01:20 by aderison          #+#    #+#             */
/*   Updated: 2024/08/11 22:27:23 by aderison         ###   ########.fr       */
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
					return (ft_printf("ERROR : %d %d\n", j, i), 0);
			}
		}
	}
	return (1);
}

static int	is_wallc(char *line)
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

int	is_valid_map(t_window *win)
{
	int	items[3];
	int	i;

	if (!win->maps)
		return (false);
	items[0] = 0;
	items[1] = 0;
	items[2] = 0;
	i = 0;
	if (!is_wallc(win->maps[i]))
		return (0);
	while (win->maps[i] && i < win->row_size)
	{
		if (win->maps[i][0] != '1' || win->maps[i][ft_strlen(win->maps[i])
			- 2] != '1')
			return (0);
		nb_items(win->maps[i], items);
		if (!win->maps[i + 1])
			if (!is_wallc(win->maps[i]))
				return (0);
		i++;
	}
	return (items[0] > 0 && items[1] == 1 && items[2] == 1);
}
