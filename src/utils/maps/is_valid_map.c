/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:01:20 by aderison          #+#    #+#             */
/*   Updated: 2024/07/24 20:32:56 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	is_wall(char *line)
{
	int	len;

	len = ft_strlen(line);
	while (--len - 1 > 0)
		if (line[len - 1] != '1')
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

int	is_valid_map(t_list **plan)
{
	t_list	*map;
	int		items[3];

	if (!plan || !*plan)
		return (false);
	map = *plan;
	items[0] = 0;
	items[1] = 0;
	items[2] = 0;
	if (!is_wall(map->content))
		return (0);
	while (map)
	{
		if (((char *)map->content)[0] != '1'
			|| ((char *)map->content)[ft_strlen(map->content) - 2] != '1')
			return (0);
		nb_items(map->content, items);
		if (!map->next)
			if (!is_wall(map->content))
				return (0);
		map = map->next;
	}
	return (items[0] > 0 && items[1] == 1 && items[2] == 1);
}
