/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 06:51:00 by aderison          #+#    #+#             */
/*   Updated: 2024/08/03 17:59:30 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// int	main(int argc, char **argv)
// {
// 	t_window	window;
// 	t_point		src;
// 	t_point		dest;

// 	if (argc != 2)
// 		return (ft_putstr_fd(RED ARG_ERR RESET, 2));
// 	if (file_exist(argv[1]) && file_extention(argv[1], ".ber"))
// 	{
// 		init_maps(argv[1], &window);
// 		if (!syntaxe_error(&window) || !is_valid_map(window.maps))
// 			return (ft_printf("erer"));
// 	}

// 	/* LIRE LE FICHIER .BER
// 		* verrifier les lettres x
// 		* verrifer que toutes les lignes ont la meme longueurs x
// 		* limiter le nombre de ligne x
// 		* verrfier que les collectible soit tous colectable
// 		* verrifier que la map est fermee X
// 		* verrfier qu'elle est possible
// 		* verrifier qu'il y a au moins un collectible
// 		*/
// 	ft_printf("alors %d", window.col_size);
// 	return (0);
// }

#include <stdio.h>
#define WIDTH 10
#define HEIGHT 10

void	print_path(t_node *end)
{
	t_node	*current;
	char	grid[13][27];
	int		i;
	int		j;

	i = 0;
	while (i < 12)
	{
		j = 0;
		while (j < 26)
		{
			grid[i][j] = '.';
			j++;
		}
		i++;
	}
	current = end;
	while (current)
	{
		grid[current->pos.y][current->pos.x] = '*';
		current = current->parent;
	}
	i = 0;
	while (i < 12)
	{
		j = 0;
		while (j < 26)
		{
			printf("%c ", grid[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_astar		tastar;
	t_node		*result;
	int			i;
	int			j;
	t_window	window;

	if (argc != 2)
		return (ft_putstr_fd(RED ARG_ERR RESET, 2));
	if (file_exist(argv[1]) && file_extention(argv[1], ".ber"))
	{
		init_maps(argv[1], &window);
		if (!syntaxe_error(&window) || !is_valid_map(window.maps))
			return (ft_printf("erer"));
	}
	tastar.width = window.col_size;
	tastar.height = window.row_size;
	tastar.start.x = 1;
	tastar.start.y = 1;
	tastar.end.x = 4;
	tastar.end.y = 8;
	tastar.grid = malloc(sizeof(t_node *) * window.row_size);
	i = 0;
	while (i < window.row_size)
	{
		tastar.grid[i] = malloc(sizeof(t_node) * window.col_size);
		j = 0;
		while (j < window.col_size)
		{
			tastar.grid[i][j] = *create_node(j, i);
			tastar.grid[i][j].h = heuristic((t_point){j, i}, tastar.end);
			if (window.maps[i][j] == '1')
				tastar.grid[i][j].g = -1;
			else
				tastar.grid[i][j].g = INT_MAX;
			j++;
		}
		i++;
	}
	tastar.grid[tastar.start.y][tastar.start.x].g = 0;
	tastar.grid[tastar.start.y][tastar.start.x].f = tastar.grid[tastar.start.y][tastar.start.x].h;
	// Ajout de quelques obstacles
	tastar.grid[3][1].g = -1;
	tastar.grid[3][2].g = -1;
	tastar.grid[3][3].g = -1;
	tastar.grid[3][4].g = -1;
	tastar.grid[3][5].g = -1;
	tastar.grid[3][6].g = -1;
	tastar.grid[3][7].g = -1;
	tastar.grid[3][8].g = -1;
	tastar.grid[3][9].g = -1;
	tastar.grid[3][5].g = -1;
	tastar.grid[4][3].g = -1;
	tastar.grid[7][4].g = -1;
	tastar.grid[7][5].g = -1;
	tastar.grid[8][5].g = -1;
	tastar.grid[5][3].g = -1;
	// Afficher la grille initiale
	printf("Initial grid:\n");
	for (i = 0; i < window.row_size; i++)
	{
		for (j = 0; j < window.col_size; j++)
		{
			if (i == tastar.start.y && j == tastar.start.x)
				printf("S ");
			else if (i == tastar.end.y && j == tastar.end.x)
				printf("E ");
			else if (tastar.grid[i][j].g == -1)
				printf("# ");
			else
				printf(". ");
		}
		printf("\n");
	}
	result = astar(&tastar);
	if (result)
	{
		printf("Path found!\n");
		print_path(result);
	}
	else
		printf("No path found.\n");
	free_grid(&tastar);
	return (0);
}

/*

 -------------------------------------
|                  .                  |
| /!\ Attention free la list maps /!\ |
|                  .                  |
 -------------------------------------

*/