#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROW 5
#define COL 5

typedef struct
{
	int row, col;
}			t_point;

typedef struct
{
	int f, g, h;
	t_point	parent;
}			t_node;

typedef struct
{
	t_point	point;
	t_node	node;
}			t_cell;

int	is_valid(int row, int col)
{
	return (row >= 0 && row < ROW && col >= 0 && col < COL);
}

int	is_unblocked(int grid[ROW][COL], int row, int col)
{
	return (grid[row][col] == 1);
}

int	is_destination(t_point src, t_point dest)
{
	return (src.row == dest.row && src.col == dest.col);
}

int	calculate_h_value(t_point src, t_point dest)
{
	return (abs(src.row - dest.row) + abs(src.col - dest.col));
}

void	trace_path(t_node node_details[ROW][COL], t_point dest)
{
	int	row;
	int	col;
	int	temp_row;
	int	temp_col;

	row = dest.row;
	col = dest.col;
	printf("The path is: \n");
	while (!(node_details[row][col].parent.row == row
			&& node_details[row][col].parent.col == col))
	{
		printf("-> (%d, %d) ", row, col);
		temp_row = node_details[row][col].parent.row;
		temp_col = node_details[row][col].parent.col;
		row = temp_row;
		col = temp_col;
	}
	printf("-> (%d, %d)\n", row, col);
}

void	initialize_node_details(t_node node_details[ROW][COL])
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			node_details[i][j].f = FLT_MAX;
			node_details[i][j].g = FLT_MAX;
			node_details[i][j].h = FLT_MAX;
			node_details[i][j].parent.row = -1;
			node_details[i][j].parent.col = -1;
		}
	}
}

void	add_to_open_list(t_cell *open_list, int *open_list_size, t_point point,
		t_node node)
{
	open_list[*open_list_size].point = point;
	open_list[*open_list_size].node = node;
	(*open_list_size)++;
}

void	remove_from_open_list(t_cell *open_list, int *open_list_size, int index)
{
	open_list[index] = open_list[*open_list_size - 1];
	(*open_list_size)--;
}

void	update_node_details(t_node *node, int g_new, int h_new, t_point parent)
{
	node->g = g_new;
	node->h = h_new;
	node->f = g_new + h_new;
	node->parent = parent;
}

void	a_star_search(int grid[ROW][COL], t_point src, t_point dest)
{
	int		closed_list[ROW][COL];
	t_node	node_details[ROW][COL];
	t_cell	open_list[ROW * COL];
	int		open_list_size;
	int		found_dest;
	t_cell	current_cell;
	int		directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
	int		index;
	t_point	point;
	int		row;
	int		col;
	int		g_new;
	int		h_new;
	int		f_new;

	open_list_size = 0;
	found_dest = 0;
	if (!is_valid(src.row, src.col) || !is_valid(dest.row, dest.col))
	{
		printf("Source or the destination is invalid\n");
		return ;
	}
	if (!is_unblocked(grid, src.row, src.col) || !is_unblocked(grid, dest.row,
			dest.col))
	{
		printf("Source or the destination is blocked\n");
		return ;
	}
	if (is_destination(src, dest))
	{
		printf("We are already at the destination\n");
		return ;
	}
	memset(closed_list, 0, sizeof(closed_list));
	initialize_node_details(node_details);
	node_details[src.row][src.col].f = 0;
	node_details[src.row][src.col].g = 0;
	node_details[src.row][src.col].h = 0;
	node_details[src.row][src.col].parent = src;
	add_to_open_list(open_list, &open_list_size, src,
		node_details[src.row][src.col]);
	while (open_list_size > 0)
	{
		current_cell = open_list[0];
		index = 0;
		for (int i = 1; i < open_list_size; i++)
		{
			if (open_list[i].node.f < current_cell.node.f)
			{
				current_cell = open_list[i];
				index = i;
			}
		}
		point = current_cell.point;
		remove_from_open_list(open_list, &open_list_size, index);
		closed_list[point.row][point.col] = 1;
		for (int d = 0; d < 4; d++)
		{
			row = point.row + directions[d][0];
			col = point.col + directions[d][1];
			if (is_valid(row, col))
			{
				if (is_destination((t_point){row, col}, dest))
				{
					node_details[row][col].parent = point;
					trace_path(node_details, dest);
					found_dest = 1;
					return ;
				}
				else if (!closed_list[row][col] && is_unblocked(grid, row, col))
				{
					g_new = node_details[point.row][point.col].g + 1;
					h_new = calculate_h_value((t_point){row, col}, dest);
					f_new = g_new + h_new;
					if (node_details[row][col].f == FLT_MAX
						|| node_details[row][col].f > f_new)
					{
						update_node_details(&node_details[row][col], g_new,
							h_new, point);
						add_to_open_list(open_list, &open_list_size,
							(t_point){row, col}, node_details[row][col]);
					}
				}
			}
		}
	}
	if (!found_dest)
	{
		printf("Failed to find the destination cell\n");
	}
}

int	main(void)
{
	int		grid[ROW][COL] = {{1, 1, 1, 1, 1}, {1, 0, 1, 0, 1}, {1, 1, 1, 1, 1},
				{1, 0, 1, 0, 1}, {1, 1, 1, 1, 1}};
	t_point	src;
	t_point	dest;

	src = {0, 0};
	dest = {4, 4};
	a_star_search(grid, src, dest);
	return (0);
}
