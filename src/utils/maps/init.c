/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:23:16 by aderison          #+#    #+#             */
/*   Updated: 2024/07/25 21:04:56 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	set_maps(char *path, t_window *win)
{
	char	*line;
	int		fd;
	int		i;

	if (!path)
	{
		(ft_putstr_fd(YELLOW NULL_PTR RESET, 2));
		return ;
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return ;
	line = get_next_line(fd);
	i = -1;
	while (line)
	{
		win->maps[++i] = line;
		line = get_next_line(fd);
	}
	close(fd);
}

void	init_maps(char *path, t_window *win)
{
	char	*line;
	int		fd;
	int		i;

	if (!path)
	{
		(ft_putstr_fd(YELLOW NULL_PTR RESET, 2));
		return ;
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return ;
	line = get_next_line(fd);
	win->col_size = ft_strlen(line);
	i = 0;
	while (line)
	{
		i++;
		line = get_next_line(fd);
	}
	win->maps = (char **)malloc(sizeof(char *) * i);
	win->row_size = i;
	set_maps(path, win);
	close(fd);
}
