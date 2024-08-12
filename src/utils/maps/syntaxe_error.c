/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:31:13 by aderison          #+#    #+#             */
/*   Updated: 2024/08/11 22:15:07 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	syntaxe_error(t_window *win)
{
	int		i;
	char	**tmp;
	int		size;

	i = 0;
	tmp = win->maps;
	size = ft_strlen(tmp[i]);
	if (size > 1920 / 32)
		return (false);
	while (i < win->row_size)
	{
		if (i > 1080 / 32)
			return (false);
		if (!line_checkchr(tmp[i]) || !line_checknbr(tmp[i], size))
			return (false);
		i++;
	}
	return (true);
}
