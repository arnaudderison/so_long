/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 07:06:30 by aderison          #+#    #+#             */
/*   Updated: 2024/07/30 20:11:44 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft.h"
# include "maps.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>

# define RED "\x1B[31m"
# define GREEN "\x1B[32m"
# define YELLOW "\x1B[33m"
# define BLUE "\x1B[34m"
# define MAG "\x1B[35m"
# define CYN "\x1B[36m"
# define RESET "\x1B[0m"

# define ARG_ERR "Number(s) of arg(s) is invalid"
# define NULL_PTR "Pointer NULL"

typedef enum e_bool
{
	false,
	true
}		t_bool;

t_bool	file_exist(const char *path);
t_bool	file_extention(const char *path, const char *ext);
t_bool	line_checkchr(char *line);
t_bool	line_checknbr(char *line, int size);
void	init_maps(char *path, t_window *win);
#endif
