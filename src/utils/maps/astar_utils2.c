/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astar_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 22:19:36 by aderison          #+#    #+#             */
/*   Updated: 2024/07/30 22:20:20 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_src_dest(t_point src, t_point dest, t_window *win)
{
	if (!is_valid(src.y, src.x, win) || !is_valid(dest.y, dest.x, win))
	{
		ft_printf("Source or the destination is invalid\n");
		return (0);
	}
	if (!is_unblocked(win, src.y, src.x) || !is_unblocked(win, dest.y, dest.x))
	{
		ft_printf("Source or the destination is blocked\n");
		return (0);
	}
	if (is_destination(src, dest))
	{
		ft_printf("We are already at the destination\n");
		return (0);
	}
	return (1);
}
