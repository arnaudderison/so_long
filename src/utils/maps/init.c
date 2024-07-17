/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:23:16 by aderison          #+#    #+#             */
/*   Updated: 2024/07/17 23:01:21 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_maps(char *path, t_window *win)
{
	char	*line;
	int		fd;
	t_list	*new;

	if (!path)
	{
		(ft_putstr_fd(YELLOW NULL_PTR RESET, 2));
		return ;
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return ;
	line = get_next_line(fd);
	while (line)
	{
		new = ft_lstnew(line);
		ft_lstadd_back(&win->maps, new);
		line = get_next_line(fd);
	}
	close(fd);
}
