/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 21:24:24 by aderison          #+#    #+#             */
/*   Updated: 2024/07/24 15:25:06 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPS_H
# define MAPS_H

# include "so_long.h"

typedef struct s_window
{
	t_list	*maps;
}			t_window;

int			syntaxe_error(t_window *win);
int			is_valid_map(t_list **plan);

#endif