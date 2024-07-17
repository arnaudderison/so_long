/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:31:13 by aderison          #+#    #+#             */
/*   Updated: 2024/07/17 23:18:20 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	syntaxe_error(t_window *win)
{
	int		i;
	t_list	*tmp;
	int		size;

	i = -1;
	tmp = win->maps;
	size = ft_strlen(tmp->content);
	if (size > 1920 / 32)
		return (false);
	while (++i < ft_lstsize(win->maps))
	{
		if (i > 1080 / 32)
			return (false);
		if (!line_checkchr(tmp->content) || !line_checknbr(tmp->content, size))
			return (false);
		tmp = tmp->next;
	}
	return (true);
}
