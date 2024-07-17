/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_checknbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:18:45 by aderison          #+#    #+#             */
/*   Updated: 2024/07/17 18:19:13 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_bool	line_checknbr(char *line, int size)
{
	if (!ft_strchr(line, '\n'))
		size--;
	return (ft_strlen(line) == size);
}
