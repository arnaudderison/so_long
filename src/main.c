/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 06:51:00 by aderison          #+#    #+#             */
/*   Updated: 2024/07/30 22:03:21 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_window	window;
	t_point		src;
	t_point		dest;

	if (argc != 2)
		return (ft_putstr_fd(RED ARG_ERR RESET, 2));
	if (file_exist(argv[1]) && file_extention(argv[1], ".ber"))
	{
		init_maps(argv[1], &window);
		if (!syntaxe_error(&window) || !is_valid_map(window.maps))
			return (ft_printf("erer"));
	}
	src.x = 5;
	src.y = 3;
	dest.x = 5;
	dest.y = 3;
	astar(window.maps, src, dest, &window);
	/* LIRE LE FICHIER .BER
		* verrifier les lettres x
		* verrifer que toutes les lignes ont la meme longueurs x
		* limiter le nombre de ligne x
		* verrfier que les collectible soit tous colectable
		* verrifier que la map est fermee X
		* verrfier qu'elle est possible
		* verrifier qu'il y a au moins un collectible
		*/
	ft_printf("alors %d", window.col_size);
	return (0);
}

/*

 -------------------------------------
|                  .                  |
| /!\ Attention free la list maps /!\ |
|                  .                  |
 -------------------------------------

*/