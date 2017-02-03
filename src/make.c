// 42 header here

#include "fdf.h"

int		ft_abs(int i)
{
	return (i < 0 ? -i : i);
}

t_v3	**copy_v3(t_v3 **v3grid, t_info info)
{
	int y;
	int x;
	t_v3 **tmp_v3grid;

	y = 0;
	tmp_v3grid = (t_v3 **)malloc(sizeof(t_v3*) * info.numlines + 1);
	while (y < info.numlines)
	{
		tmp_v3grid[y] = (t_v3*)malloc(sizeof(t_v3) * info.numcols + 1);
		y++;
	}
	y = 0;
	while (y < info.numlines - 1)
	{
		x = 0;
		while (x < info.numcols)
		{
			tmp_v3grid[y][x] = v3grid[y][x];
			x++;
		}
		y++;
	}
	return (tmp_v3grid);
}

t_v3	**make_v3grid(t_info info) // goal of this is to go through the file and create
{
	int		count;
	int		count2;
	int		countz;
	t_v3	**grid;

	count = 0;
	countz = 0;
	grid = (t_v3**)malloc(sizeof(t_v3 *) * info.numlines + 1);
	while (count < info.numlines)
	{
		count2 = 0;
		grid[count] = (t_v3*)malloc(sizeof(t_v3) * info.numcols + 1);
		while (count2 < info.numcols)
		{
			grid[count][count2].x = info.zoom * (count2 - info.numcols / 2);
			grid[count][count2].y = info.zoom * (count - info.numlines / 2);
			grid[count][count2].z = (info.zoom / 2.5) * (info.zmap[countz]);
			countz++;
			count2++;
		}
		count++;
	}
	return (grid);
}

t_v2	**make_pts(t_info info, t_v3 **v3grid)
{
	t_v2	**pts;
	int		x;
	int		y;

	x = 0;
	y = 0;
	pts = (t_v2**)malloc(sizeof(t_v2*) * info.numlines);
	while (y < info.numlines)
	{
		pts[y] = (t_v2*)malloc(sizeof(t_v2) * info.numcols);
		y++;
	}
	y = 0;
	while (y < info.numlines - 1)
	{
		while (x < info.numcols)
		{
			pts[y][x].x = v3grid[y][x].x + info.width / 2;
			pts[y][x].y = v3grid[y][x].y + info.height / 2;
			x++;
		}
		x = 0;
		y++;
	}
	return	(pts);
}