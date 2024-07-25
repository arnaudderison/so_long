#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define ROW 5
#define COL 5

typedef struct
{
	int row, col;
}			Point;

typedef struct
{
	int f, g, h;
	Point	parent;
}			Node;

typedef struct
{
	Point	point;
	Node	node;
}			Cell;

int	isValid(int row, int col)
{
	return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL);
}

int	isUnBlocked(int grid[ROW][COL], int row, int col)
{
	return (grid[row][col] == 1);
}

int	isDestination(Point src, Point dest)
{
	return (src.row == dest.row && src.col == dest.col);
}

int	calculateHValue(Point src, Point dest)
{
	return (abs(src.row - dest.row) + abs(src.col - dest.col));
}

void	tracePath(Node nodeDetails[ROW][COL], Point dest)
{
	int	row;
	int	col;
	int	temp_row;
	int	temp_col;

	printf("The path is: \n");
	row = dest.row;
	col = dest.col;
	while (!(nodeDetails[row][col].parent.row == row
			&& nodeDetails[row][col].parent.col == col))
	{
		printf("-> (%d, %d) ", row, col);
		temp_row = nodeDetails[row][col].parent.row;
		temp_col = nodeDetails[row][col].parent.col;
		row = temp_row;
		col = temp_col;
	}
	printf("-> (%d, %d)\n", row, col);
}

void	aStarSearch(int grid[ROW][COL], Point src, Point dest)
{
	int		closedList[ROW][COL];
	Node	nodeDetails[ROW][COL];
	Cell	openList[ROW * COL];
	int		openListSize;
	int		foundDest;
	Cell	currentCell;
	int		index;
	Point	point;
	int		newRow[] = {-1, 1, 0, 0};
	int		newCol[] = {0, 0, -1, 1};
	int		row;
	int		col;
	int		gNew;
	int		hNew;
	int		fNew;

	if (!isValid(src.row, src.col) || !isValid(dest.row, dest.col))
	{
		printf("Source or the destination is invalid\n");
		return ;
	}
	if (!isUnBlocked(grid, src.row, src.col) || !isUnBlocked(grid, dest.row,
			dest.col))
	{
		printf("Source or the destination is blocked\n");
		return ;
	}
	if (isDestination(src, dest))
	{
		printf("We are already at the destination\n");
		return ;
	}
	memset(closedList, 0, sizeof(closedList));
	int i, j;
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			nodeDetails[i][j].f = FLT_MAX;
			nodeDetails[i][j].g = FLT_MAX;
			nodeDetails[i][j].h = FLT_MAX;
			nodeDetails[i][j].parent.row = -1;
			nodeDetails[i][j].parent.col = -1;
		}
	}
	i = src.row;
	j = src.col;
	nodeDetails[i][j].f = 0.0;
	nodeDetails[i][j].g = 0.0;
	nodeDetails[i][j].h = 0.0;
	nodeDetails[i][j].parent.row = i;
	nodeDetails[i][j].parent.col = j;
	openListSize = 0;
	openList[openListSize].point = src;
	openList[openListSize].node = nodeDetails[i][j];
	openListSize++;
	foundDest = 0;
	while (openListSize > 0)
	{
		currentCell = openList[0];
		index = 0;
		for (i = 1; i < openListSize; i++)
		{
			if (openList[i].node.f < currentCell.node.f)
			{
				currentCell = openList[i];
				index = i;
			}
		}
		point = currentCell.point;
		openList[index] = openList[openListSize - 1];
		openListSize--;
		i = point.row;
		j = point.col;
		[i][j] = 1;
		for (int k = 0; k < 4; k++)
		{
			row = i + newRow[k];
			col = j + newCol[k];
			if (isValid(row, col))
			{
				if (isDestination((Point){row, col}, dest))
				{
					nodeDetails[row][col].parent.row = i;
					nodeDetails[row][col].parent.col = j;
					tracePath(nodeDetails, dest);
					foundDest = 1;
					return ;
				}
				else if (!closedList[row][col] && isUnBlocked(grid, row, col))
				{
					gNew = nodeDetails[i][j].g + 1;
					hNew = calculateHValue((Point){row, col}, dest);
					fNew = gNew + hNew;
					if (nodeDetails[row][col].f == FLT_MAX
						|| nodeDetails[row][col].f > fNew)
					{
						openList[openListSize].point = (Point){row, col};
						openList[openListSize].node.f = fNew;
						openList[openListSize].node.g = gNew;
						openList[openListSize].node.h = hNew;
						openList[openListSize].node.parent.row = i;
						openList[openListSize].node.parent.col = j;
						openListSize++;
						nodeDetails[row][col] = openList[openListSize - 1].node;
					}
				}
			}
		}
	           
}

int	main(void)
{
	int		grid[ROW][COL] = {{1, 1, 1, 1, 1}, {1, 0, 1, 0, 1}, {1, 1, 1, 1, 1},
				{1, 0, 1, 0, 1}, {1, 1, 1, 1, 1}};
	Point	src;
	Point	dest;

	src = {0, 0};
	dest = {4, 4};
	aStarSearch(grid, src, dest);
	return (0);
}
